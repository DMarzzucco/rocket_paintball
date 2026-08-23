use std::time::Duration;

pub const CODE: u32 = 5555;
pub const MAX_ATTEMPTS: u8 = 3;
pub const LOCK_DURATION: Duration = Duration::from_secs(2 * 10); // 2 minutos de espera
pub const ARM_DURATION: Duration = Duration::from_secs(4 * 10); // 40 minutos
pub const MIN_ARM_DURATION: Duration = Duration::from_secs(1); // por debajo de esto, se lanza directamente

