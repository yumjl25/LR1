use std::rc::Rc;
use std::cell::RefCell;

pub type Link = Option<Rc<RefCell<QNode>>>;

pub struct QNode {
    pub data: String,
    pub next: Link,
}

pub struct Queue {
    pub head: Link,
    pub tail: Link,
}

impl Queue {
    pub fn new() -> Queue {
        Queue { head: None, tail: None }
    }

    pub fn is_empty(&self) -> bool {
        self.head.is_none()
    }

    pub fn push(&mut self, value: String) {
        let node = Rc::new(RefCell::new(QNode { data: value, next: None }));
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
    }

    pub fn pop(&mut self) -> Option<String> {
        match self.head.take() {
            None => None,
            Some(head) => {
                let value = head.borrow().data.clone();
                let next = head.borrow().next.clone();
                self.head = next;
                if self.head.is_none() {
                    self.tail = None;
                }
                Some(value)
            }
        }
    }

    pub fn get(&self) -> Option<String> {
        match &self.head {
            None => None,
            Some(head) => Some(head.borrow().data.clone()),
        }
    }

    pub fn print(&self) {
        if self.is_empty() {
            println!("QUEUE: empty");
            return;
        }
        println!("QUEUE:");
        let mut cur = self.head.clone();
        while let Some(node) = cur {
            println!("  {}", node.borrow().data);
            cur = node.borrow().next.clone();
        }
    }
}