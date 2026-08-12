use std::io::{self, Write};
use std::time::{Duration, Instant};

const CODE: u32 = 5555;
const MAX_ATTEMPTS: u8 = 3;
const LOCK_DURATION: Duration = Duration::from_secs(2 * 10); // 2 minutos de espera
const ARM_DURATION: Duration = Duration::from_secs(4 * 10); // 40 minutos
const MIN_ARM_DURATION: Duration = Duration::from_secs(1); // por debajo de esto, se lanza directamente

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

/// Formatea una duración en minutos si alcanza el minuto, o en segundos si no.
fn format_duration(d: Duration) -> String {
    let secs = d.as_secs();
    if secs >= 60 {
        format!("{} minutos", secs / 60)
    } else {
        format!("{} segundos", secs)
    }
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
                println!("Se agotó el tiempo: se inicia el lanzamiento.");
            }
            _ => {}
        }
    }

    fn submit_code(&mut self, code: u32) {
        self.tick();

        match self.state {
            PanelState::Fired => {
                println!("El cohete ya fue lanzado. No hay nada que hacer.");
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
                        "Cohete activado, el lanzamiento comenzará en {}. Para desactivarlo, volvé a ingresar la clave.",
                        format_duration(ARM_DURATION)
                    );
                } else {
                    self.register_failed_attempt();
                }
            }
            PanelState::Armed { fires_at } => {
                if code == self.code {
                    self.state = PanelState::Idle;
                    self.attempts = 0;
                    println!("Lanzamiento cancelado.");
                } else {
                    self.accelerate_launch(fires_at);
                }
            }
        }
    }

    /// Clave incorrecta durante el armado: se acorta a la mitad el tiempo restante.
    fn accelerate_launch(&mut self, fires_at: Instant) {
        let remaining = fires_at.saturating_duration_since(Instant::now());
        let shortened = remaining / 2;

        if shortened <= MIN_ARM_DURATION {
            self.state = PanelState::Fired;
            println!("Clave incorrecta. Se agotó el tiempo: se inicia el lanzamiento.");
        } else {
            self.state = PanelState::Armed {
                fires_at: Instant::now() + shortened,
            };
            println!(
                "Clave incorrecta, acelerando tiempo de lanzamiento. Quedan {}.",
                format_duration(shortened)
            );
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

    println!("Ingresá la clave.");

    loop {
        panel.tick();
        if panel.is_fired() {
            break;
        }

        print!("Clave: ");
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
