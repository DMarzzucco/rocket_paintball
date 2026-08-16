use std::time::Instant;
use crate::utils::constants::{ARM_DURATION, LOCK_DURATION, MAX_ATTEMPTS, MIN_ARM_DURATION};
use crate::utils::format_duration::format_duration;


#[derive(Debug)]
enum PanelState {
    Idle,
    Locked { until: Instant },
    Armed { fires_at: Instant },
    Fired,
}

#[derive(Debug)]
pub struct Panel {
    code: u32,
    attempts: u8,
    state: PanelState,
}

impl Panel {
    pub fn new(code: u32) -> Self {
        Panel {
            code,
            attempts: 0,
            state: PanelState::Idle,
        }
    }

    pub fn is_fired(&self) -> bool {
        matches!(self.state, PanelState::Fired)
    }

    /// Actualiza el estado si un temporizador ya venció.
    pub fn tick(&mut self) {
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

    pub fn submit_code(&mut self, code: u32) {
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