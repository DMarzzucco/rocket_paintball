use std::io::{self, Write};
use std::time::{Duration, Instant};

const CODE: u32 = 15412435;
const MAX_ATTEMPTS: u8 = 3;
const LOCK_DURATION: Duration = Duration::from_secs(2 * 10);
const ARM_DURATION: Duration = Duration::from_secs(4 * 10);

#[derive(Debug)]
enum PanelState {
    Idle,
    Locked { until: Instant },
    Armed { fires_at: Instant },
    Fired,
}

#[derive(Debug)]
struct Panel {
    code: u32,
    attempts: u8,
    state: PanelState,
}

impl Panel {
    fn new(code: u32) -> Self {
        Panel {
            code,
            attempts: 0,
            state: PanelState::Idle,
        }
    }

    fn is_fired(&self) -> bool {
        matches!(self.state, PanelState::Fired)
    }

    /// Actualiza el estado si un temporizador ya venció.
    fn tick(&mut self) {
        match self.state {
            PanelState::Locked { until } if Instant::now() >= until => {
                self.state = PanelState::Idle;
                self.attempts = 0;
                println!("El panel se desbloqueó. Podés intentar de nuevo.");
            }
            PanelState::Armed { fires_at } if Instant::now() >= fires_at => {
                self.state = PanelState::Fired;
                println!("BOOM. Se agotó el tiempo: la ojiva se disparó.");
            }
            _ => {}
        }
    }

    fn submit_code(&mut self, code: u32) {
        self.tick();

        match self.state {
            PanelState::Fired => {
                println!("El sistema ya detonó. No hay nada que hacer.");
            }
            PanelState::Locked { until } => {
                let remaining = until.saturating_duration_since(Instant::now());
                println!("Panel bloqueado. Esperá {}s.", remaining.as_secs());
            }
            PanelState::Idle => {
                if code == self.code {
                    self.state = PanelState::Armed {
                        fires_at: Instant::now() + ARM_DURATION,
                    };
                    self.attempts = 0;
                    println!(
                        "Válvula armada. Se disparará en {}s si no se desactiva con el mismo código.",
                        ARM_DURATION.as_secs()
                    );
                } else {
                    self.register_failed_attempt();
                }
            }
            PanelState::Armed { .. } => {
                if code == self.code {
                    self.state = PanelState::Idle;
                    self.attempts = 0;
                    println!("Válvula desactivada correctamente.");
                } else {
                    self.register_failed_attempt();
                }
            }
        }
    }

    fn register_failed_attempt(&mut self) {
        self.attempts += 1;
        if self.attempts >= MAX_ATTEMPTS {
            self.state = PanelState::Locked {
                until: Instant::now() + LOCK_DURATION,
            };
            self.attempts = 0;
            println!(
                "Código incorrecto. Intentos agotados: panel bloqueado por {}s.",
                LOCK_DURATION.as_secs()
            );
        } else {
            println!("Código incorrecto ({}/{}).", self.attempts, MAX_ATTEMPTS);
        }
    }
}

fn main() {
    let mut panel = Panel::new(CODE);
    let stdin = io::stdin();

    loop {
        panel.tick();
        if panel.is_fired() {
            break;
        }

        print!("Ingresá el código (o 'salir'): ");
        io::stdout().flush().unwrap();

        let mut line = String::new();
        match stdin.read_line(&mut line) {
            Ok(0) | Err(_) => break, // EOF o error de lectura: terminar
            Ok(_) => {}
        }
        let line = line.trim();

        if line.eq_ignore_ascii_case("salir") {
            println!("Saliendo.");
            break;
        }

        match line.parse::<u32>() {
            Ok(code) => panel.submit_code(code),
            Err(_) => println!("Ingresá solo números."),
        }
    }
}
