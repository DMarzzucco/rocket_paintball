use std::time::Duration;

pub fn format_duration(d: Duration) -> String {
    let secs = d.as_secs();
    if secs >= 60 {
        format!("{} minutos", secs / 60)
    } else {
        format!("{} segundos", secs)
    }
}