use std::rc::Rc;
use std::cell::RefCell;

pub type Link = Option<Rc<RefCell<FNode>>>;

pub struct FNode {
    pub data: String,
    pub next: Link,
}

pub struct ForwardList {
    pub head: Link,
    pub tail: Link,
    pub size: usize,
}

impl ForwardList {
    pub fn new() -> ForwardList {
        ForwardList { head: None, tail: None, size: 0 }
    }

    pub fn is_empty(&self) -> bool {
        self.head.is_none()
    }

    pub fn push_head(&mut self, value: String) {
        let node = Rc::new(RefCell::new(FNode { data: value, next: self.head.clone() }));
        if self.tail.is_none() {
            self.tail = Some(Rc::clone(&node));
        }
        self.head = Some(node);
        self.size += 1;
    }

    pub fn push_tail(&mut self, value: String) {
        let node = Rc::new(RefCell::new(FNode { data: value, next: None }));
        match &self.tail {
            None => {
                self.head = Some(Rc::clone(&node));
                self.tail = Some(Rc::clone(&node));
            }
            Some(tail) => {
                tail.borrow_mut().next = Some(Rc::clone(&node));
                self.tail = Some(Rc::clone(&node));
            }
        }
        self.size += 1;
    }

    pub fn push_before(&mut self, target: String, value: String) {
        if let Some(head) = self.head.clone() {
            if head.borrow().data == target {
                self.push_head(value);
                return;
            }
        }
        let mut cur = self.head.clone();
        while let Some(node) = cur {
            let next = node.borrow().next.clone();
            if let Some(n) = next {
                if n.borrow().data == target {
                    let new_node = Rc::new(RefCell::new(FNode {
                        data: value,
                        next: Some(Rc::clone(&n)),
                    }));
                    node.borrow_mut().next = Some(new_node);
                    self.size += 1;
                    return;
                }
            }
            cur = node.borrow().next.clone();
        }
        println!("Target not found");
    }

    pub fn push_after(&mut self, target: String, value: String) {
        let mut cur = self.head.clone();
        while let Some(node) = cur {
            if node.borrow().data == target {
                let new_node = Rc::new(RefCell::new(FNode {
                    data: value,
                    next: node.borrow().next.clone(),
                }));
                node.borrow_mut().next = Some(Rc::clone(&new_node));
                if let Some(tail) = &self.tail {
                    if Rc::ptr_eq(tail, &node) {
                        self.tail = Some(new_node);
                    }
                }
                self.size += 1;
                return;
            }
            cur = node.borrow().next.clone();
        }
        println!("Target not found");
    }

    pub fn get_head(&self) -> Option<String> {
        self.head.as_ref().map(|node| node.borrow().data.clone())
    }

    pub fn get_tail(&self) -> Option<String> {
        self.tail.as_ref().map(|node| node.borrow().data.clone())
    }

    pub fn get_at(&self, index: usize) -> Option<String> {
        if index >= self.size {
            return None;
        }
        let mut cur = self.head.clone();
        for _ in 0..index {
            if let Some(node) = cur {
                cur = node.borrow().next.clone();
            } else {
                return None;
            }
        }
        cur.map(|node| node.borrow().data.clone())
    }

    pub fn del_head(&mut self) -> Option<String> {
        match self.head.take() {
            None => None,
            Some(head) => {
                let value = head.borrow().data.clone();
                let next = head.borrow().next.clone();
                self.head = next;
                if self.head.is_none() {
                    self.tail = None;
                }
                self.size -= 1;
                Some(value)
            }
        }
    }

    pub fn del_tail(&mut self) -> Option<String> {
        if self.is_empty() {
            return None;
        }
        if let (Some(h), Some(t)) = (&self.head, &self.tail) {
            if Rc::ptr_eq(h, t) {
                return self.del_head();
            }
        }
        let mut cur = self.head.clone();
        while let Some(node) = cur {
            let next = node.borrow().next.clone();
            if let Some(n) = next {
                if let Some(tail) = &self.tail {
                    if Rc::ptr_eq(&n, tail) {
                        let value = n.borrow().data.clone();
                        node.borrow_mut().next = None;
                        self.tail = Some(Rc::clone(&node));
                        self.size -= 1;
                        return Some(value);
                    }
                }
                cur = Some(n);
            } else {
                break;
            }
        }
        None
    }

    pub fn del_value(&mut self, value: String) -> bool {
        if let Some(head) = self.head.clone() {
            if head.borrow().data == value {
                self.del_head();
                return true;
            }
        }
        let mut cur = self.head.clone();
        while let Some(node) = cur {
            let next = node.borrow().next.clone();
            if let Some(n) = next {
                if n.borrow().data == value {
                    let after = n.borrow().next.clone();
                    node.borrow_mut().next = after;
                    if let Some(tail) = &self.tail {
                        if Rc::ptr_eq(tail, &n) {
                            self.tail = Some(Rc::clone(&node));
                        }
                    }
                    self.size -= 1;
                    return true;
                }
                cur = Some(n);
            } else {
                break;
            }
        }
        false
    }

    pub fn search(&self, value: String) -> bool {
        let mut cur = self.head.clone();
        while let Some(node) = cur {
            if node.borrow().data == value {
                return true;
            }
            cur = node.borrow().next.clone();
        }
        false
    }

    pub fn print(&self) {
        if self.is_empty() {
            println!("LIST: empty");
            return;
        }
        println!("LIST:");
        let mut cur = self.head.clone();
        while let Some(node) = cur {
            println!("  {}", node.borrow().data);
            cur = node.borrow().next.clone();
        }
    }
}