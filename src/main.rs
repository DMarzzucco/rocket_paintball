mod utils;

use std::io::{self, Write};
use utils::constants::CODE;
use utils::panel_contro::Panel;


fn main() {
    let stdin = io::stdin();
    let mut panel = Panel::new(CODE);

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
