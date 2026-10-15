mod stack;
mod queue;
mod array;
mod forward_list;
mod list;
mod storage;

use storage::Storage;

fn main() {
    let args: Vec<String> = std::env::args().collect();

    let mut filename = String::new();
    let mut query = String::new();

    let mut i = 1;
    while i < args.len() {
        if args[i] == "--file" && i + 1 < args.len() {
            filename = args[i + 1].clone();
            i += 2;
        } else if args[i] == "--query" && i + 1 < args.len() {
            query = args[i + 1].clone();
            i += 2;
        } else {
            i += 1;
        }
    }

    if filename.is_empty() || query.is_empty() {
        eprintln!("Usage: {} --file <file> --query '<command>'", args[0]);
        std::process::exit(1);
    }

    let mut storage = Storage::new();
    storage.load(&filename);
    storage.execute(&query, false);
    storage.save(&filename);
}