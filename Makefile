run:
	cargo run

imp:
	cargo build

build-windows:
	cargo build --release --target x86_64-pc-windows-gnu
build:
	cargo build ./target/debug/build
