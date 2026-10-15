use crate::stack::Stack;
use crate::queue::Queue;
use crate::array::Array;
use crate::forward_list::ForwardList;
use crate::list::List;


pub struct StackEntry {
    pub name: String,
    pub stack: Stack,
    pub next: Option<Box<StackEntry>>,
}

pub struct QueueEntry {
    pub name: String,
    pub queue: Queue,
    pub next: Option<Box<QueueEntry>>,
}

pub struct ArrayEntry {
    pub name: String,
    pub array: Array,
    pub next: Option<Box<ArrayEntry>>,
}

pub struct FListEntry {
    pub name: String,
    pub list: ForwardList,
    pub next: Option<Box<FListEntry>>,
}

pub struct ListEntry {
    pub name: String,
    pub list: List,
    pub next: Option<Box<ListEntry>>,
}

pub struct Storage {
    pub stacks: Option<Box<StackEntry>>,
    pub queues: Option<Box<QueueEntry>>,
    pub arrays: Option<Box<ArrayEntry>>,
    pub flists: Option<Box<FListEntry>>,
    pub lists:  Option<Box<ListEntry>>,
}


fn find_or_create_stack<'a>(link: &'a mut Option<Box<StackEntry>>, name: &str) -> &'a mut Stack {
    match link {
        None => {
            *link = Some(Box::new(StackEntry {
                name: name.to_string(),
                stack: Stack::new(),
                next: None,
            }));
            match link {
                Some(e) => &mut e.stack,
                None => unreachable!(),
            }
        }
        Some(entry) => {
            if entry.name == name {
                &mut entry.stack
            } else {
                find_or_create_stack(&mut entry.next, name)
            }
        }
    }
}

fn find_or_create_queue<'a>(link: &'a mut Option<Box<QueueEntry>>, name: &str) -> &'a mut Queue {
    match link {
        None => {
            *link = Some(Box::new(QueueEntry {
                name: name.to_string(),
                queue: Queue::new(),
                next: None,
            }));
            match link {
                Some(e) => &mut e.queue,
                None => unreachable!(),
            }
        }
        Some(entry) => {
            if entry.name == name {
                &mut entry.queue
            } else {
                find_or_create_queue(&mut entry.next, name)
            }
        }
    }
}

fn find_or_create_array<'a>(link: &'a mut Option<Box<ArrayEntry>>, name: &str) -> &'a mut Array {
    match link {
        None => {
            *link = Some(Box::new(ArrayEntry {
                name: name.to_string(),
                array: Array::new(),
                next: None,
            }));
            match link {
                Some(e) => &mut e.array,
                None => unreachable!(),
            }
        }
        Some(entry) => {
            if entry.name == name {
                &mut entry.array
            } else {
                find_or_create_array(&mut entry.next, name)
            }
        }
    }
}

fn find_or_create_flist<'a>(link: &'a mut Option<Box<FListEntry>>, name: &str) -> &'a mut ForwardList {
    match link {
        None => {
            *link = Some(Box::new(FListEntry {
                name: name.to_string(),
                list: ForwardList::new(),
                next: None,
            }));
            match link {
                Some(e) => &mut e.list,
                None => unreachable!(),
            }
        }
        Some(entry) => {
            if entry.name == name {
                &mut entry.list
            } else {
                find_or_create_flist(&mut entry.next, name)
            }
        }
    }
}

fn find_or_create_list<'a>(link: &'a mut Option<Box<ListEntry>>, name: &str) -> &'a mut List {
    match link {
        None => {
            *link = Some(Box::new(ListEntry {
                name: name.to_string(),
                list: List::new(),
                next: None,
            }));
            match link {
                Some(e) => &mut e.list,
                None => unreachable!(),
            }
        }
        Some(entry) => {
            if entry.name == name {
                &mut entry.list
            } else {
                find_or_create_list(&mut entry.next, name)
            }
        }
    }
}


fn print_if_stack(link: &Option<Box<StackEntry>>, name: &str) -> bool {
    match link {
        None => false,
        Some(e) => {
            if e.name == name { e.stack.print(); true }
            else { print_if_stack(&e.next, name) }
        }
    }
}

fn print_if_queue(link: &Option<Box<QueueEntry>>, name: &str) -> bool {
    match link {
        None => false,
        Some(e) => {
            if e.name == name { e.queue.print(); true }
            else { print_if_queue(&e.next, name) }
        }
    }
}

fn print_if_array(link: &Option<Box<ArrayEntry>>, name: &str) -> bool {
    match link {
        None => false,
        Some(e) => {
            if e.name == name { e.array.print(); true }
            else { print_if_array(&e.next, name) }
        }
    }
}

fn print_if_flist(link: &Option<Box<FListEntry>>, name: &str) -> bool {
    match link {
        None => false,
        Some(e) => {
            if e.name == name { e.list.print(); true }
            else { print_if_flist(&e.next, name) }
        }
    }
}

fn print_if_list(link: &Option<Box<ListEntry>>, name: &str) -> bool {
    match link {
        None => false,
        Some(e) => {
            if e.name == name { e.list.print(); true }
            else { print_if_list(&e.next, name) }
        }
    }
}


impl Storage {
    pub fn new() -> Storage {
        Storage {
            stacks: None,
            queues: None,
            arrays: None,
            flists: None,
            lists:  None,
        }
    }


    pub fn execute(&mut self, query: &str, quiet: bool) {
        let mut tokens: [&str; 10] = [""; 10];
        let mut n = 0;
        for word in query.split_whitespace() {
            if n >= 10 { break; }
            tokens[n] = word;
            n += 1;
        }
        if n == 0 { return; }

        let cmd = tokens[0];

        if cmd == "PRINT" && n >= 2 {
            let name = tokens[1];
            if print_if_stack(&self.stacks, name) { return; }
            if print_if_queue(&self.queues, name) { return; }
            if print_if_array(&self.arrays, name) { return; }
            if print_if_flist(&self.flists, name) { return; }
            if print_if_list(&self.lists, name) { return; }
            if !quiet { println!("Not found: {}", name); }
            return;
        }

        if n < 2 {
            if !quiet { println!("Bad command"); }
            return;
        }
        let name = tokens[1];

        if cmd == "SPUSH" && n >= 3 {
            let v = tokens[2].to_string();
            let st = find_or_create_stack(&mut self.stacks, name);
            st.push(v.clone());
            if !quiet { println!("{}", v); }
        }
        else if cmd == "SPOP" {
            let st = find_or_create_stack(&mut self.stacks, name);
            if let Some(v) = st.pop() {
                if !quiet { println!("{}", v); }
            }
        }
        else if cmd == "SGET" {
            let st = find_or_create_stack(&mut self.stacks, name);
            if let Some(v) = st.get() {
                if !quiet { println!("{}", v); }
            }
        }

        else if cmd == "QPUSH" && n >= 3 {
            let v = tokens[2].to_string();
            let q = find_or_create_queue(&mut self.queues, name);
            q.push(v.clone());
            if !quiet { println!("{}", v); }
        }
        else if cmd == "QPOP" {
            let q = find_or_create_queue(&mut self.queues, name);
            if let Some(v) = q.pop() {
                if !quiet { println!("{}", v); }
            }
        }
        else if cmd == "QGET" {
            let q = find_or_create_queue(&mut self.queues, name);
            if let Some(v) = q.get() {
                if !quiet { println!("{}", v); }
            }
        }

        else if cmd == "MPUSH" && n >= 3 {
            let v = tokens[2].to_string();
            let a = find_or_create_array(&mut self.arrays, name);
            if n >= 4 {
                let idx: usize = tokens[3].parse().unwrap_or(0);
                a.push_at(v.clone(), idx);
            } else {
                a.push(v.clone());
            }
            if !quiet { println!("{}", v); }
        }
        else if cmd == "MDEL" && n >= 3 {
            let idx: usize = tokens[2].parse().unwrap_or(0);
            let a = find_or_create_array(&mut self.arrays, name);
            if let Some(v) = a.del(idx) {
                if !quiet { println!("{}", v); }
            }
        }
        else if cmd == "MGET" && n >= 3 {
            let idx: usize = tokens[2].parse().unwrap_or(0);
            let a = find_or_create_array(&mut self.arrays, name);
            if let Some(v) = a.get(idx) {
                if !quiet { println!("{}", v); }
            }
        }
        else if cmd == "MSET" && n >= 4 {
            let idx: usize = tokens[2].parse().unwrap_or(0);
            let v = tokens[3].to_string();
            let a = find_or_create_array(&mut self.arrays, name);
            a.set(idx, v.clone());
            if !quiet { println!("{}", v); }
        }
        else if cmd == "MLEN" {
            let a = find_or_create_array(&mut self.arrays, name);
            if !quiet { println!("{}", a.len()); }
        }

        else if cmd == "FPUSH" && n >= 3 {
            let v = tokens[2].to_string();
            let fl = find_or_create_flist(&mut self.flists, name);
            if n == 3 {
                fl.push_tail(v.clone());
            } else if tokens[3] == "head" {
                fl.push_head(v.clone());
            } else if tokens[3] == "tail" {
                fl.push_tail(v.clone());
            } else if tokens[3] == "before" && n >= 5 {
                fl.push_before(tokens[4].to_string(), v.clone());
            } else if tokens[3] == "after" && n >= 5 {
                fl.push_after(tokens[4].to_string(), v.clone());
            }
            if !quiet { println!("{}", v); }
        }
        else if cmd == "FGET" && n >= 3 {
            let fl = find_or_create_flist(&mut self.flists, name);
            if tokens[2] == "head" {
                if let Some(v) = fl.get_head() { if !quiet { println!("{}", v); } }
            } else if tokens[2] == "tail" {
                if let Some(v) = fl.get_tail() { if !quiet { println!("{}", v); } }
            } else {
                let idx: usize = tokens[2].parse().unwrap_or(0);
                if let Some(v) = fl.get_at(idx) { if !quiet { println!("{}", v); } }
            }
        }
        else if cmd == "FDEL" && n >= 3 {
            let fl = find_or_create_flist(&mut self.flists, name);
            if tokens[2] == "head" {
                if let Some(v) = fl.del_head() { if !quiet { println!("{}", v); } }
            } else if tokens[2] == "tail" {
                if let Some(v) = fl.del_tail() { if !quiet { println!("{}", v); } }
            } else {
                fl.del_value(tokens[2].to_string());
            }
        }
        else if cmd == "FSEARCH" && n >= 3 {
            let fl = find_or_create_flist(&mut self.flists, name);
            if !quiet { println!("{}", if fl.search(tokens[2].to_string()) { "TRUE" } else { "FALSE" }); }
        }

        else if cmd == "LPUSH" && n >= 3 {
            let v = tokens[2].to_string();
            let l = find_or_create_list(&mut self.lists, name);
            if n == 3 {
                l.push_tail(v.clone());
            } else if tokens[3] == "head" {
                l.push_head(v.clone());
            } else if tokens[3] == "tail" {
                l.push_tail(v.clone());
            } else if tokens[3] == "before" && n >= 5 {
                l.push_before(tokens[4].to_string(), v.clone());
            } else if tokens[3] == "after" && n >= 5 {
                l.push_after(tokens[4].to_string(), v.clone());
            }
            if !quiet { println!("{}", v); }
        }
        else if cmd == "LGET" && n >= 3 {
            let l = find_or_create_list(&mut self.lists, name);
            if tokens[2] == "head" {
                if let Some(v) = l.get_head() { if !quiet { println!("{}", v); } }
            } else if tokens[2] == "tail" {
                if let Some(v) = l.get_tail() { if !quiet { println!("{}", v); } }
            } else {
                let idx: usize = tokens[2].parse().unwrap_or(0);
                if let Some(v) = l.get_at(idx) { if !quiet { println!("{}", v); } }
            }
        }
        else if cmd == "LDEL" && n >= 3 {
            let l = find_or_create_list(&mut self.lists, name);
            if tokens[2] == "head" {
                if let Some(v) = l.del_head() { if !quiet { println!("{}", v); } }
            } else if tokens[2] == "tail" {
                if let Some(v) = l.del_tail() { if !quiet { println!("{}", v); } }
            } else {
                l.del_value(tokens[2].to_string());
            }
        }
        else if cmd == "LSEARCH" && n >= 3 {
            let l = find_or_create_list(&mut self.lists, name);
            if !quiet { println!("{}", if l.search(tokens[2].to_string()) { "TRUE" } else { "FALSE" }); }
        }

        else {
            if !quiet { println!("Unknown command: {}", cmd); }
        }
    }


    pub fn load(&mut self, filename: &str) {
        let content = match std::fs::read_to_string(filename) {
            Ok(c) => c,
            Err(_) => return,
        };
        for line in content.lines() {
            if line.trim().is_empty() { continue; }
            self.execute(line, true);
        }
    }


    pub fn save(&mut self, filename: &str) {
        let mut out = String::new();

        let mut cur = &self.stacks;
        while let Some(e) = cur {
            let mut buf: Vec<String> = Vec::new();
            let mut node = e.stack.head.as_ref();
            while let Some(n) = node {
                buf.push(n.data.clone());
                node = n.next.as_ref();
            }
            for i in (0..buf.len()).rev() {
                out.push_str(&format!("SPUSH {} {}\n", e.name, buf[i]));
            }
            cur = &e.next;
        }

        let mut cur = &self.queues;
        while let Some(e) = cur {
            let mut node = e.queue.head.clone();
            while let Some(n) = node {
                out.push_str(&format!("QPUSH {} {}\n", e.name, n.borrow().data));
                node = n.borrow().next.clone();
            }
            cur = &e.next;
        }

        let mut cur = &self.arrays;
        while let Some(e) = cur {
            for i in 0..e.array.size {
                if let Some(v) = e.array.get(i) {
                    out.push_str(&format!("MPUSH {} {}\n", e.name, v));
                }
            }
            cur = &e.next;
        }

        let mut cur = &self.flists;
        while let Some(e) = cur {
            let mut node = e.list.head.clone();
            while let Some(n) = node {
                out.push_str(&format!("FPUSH {} {}\n", e.name, n.borrow().data));
                node = n.borrow().next.clone();
            }
            cur = &e.next;
        }

        let mut cur = &self.lists;
        while let Some(e) = cur {
            let mut node = e.list.head.clone();
            while let Some(n) = node {
                out.push_str(&format!("LPUSH {} {}\n", e.name, n.borrow().data));
                node = n.borrow().next.clone();
            }
            cur = &e.next;
        }

        let _ = std::fs::write(filename, out);
    }
}