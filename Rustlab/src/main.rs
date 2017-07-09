mod tree;
mod top;

extern crate regex;

use std::fmt::Display;
use std::cmp::Ordering;
use std::io::BufRead;
use regex::Regex;

impl<'a, T: Ord + 'a + Display> Display for tree::IteratorResult<'a, T> {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "({}, {})", self.value, self.count)
    }
}

impl<'a, T: Ord + 'a> Ord for tree::IteratorResult<'a, T> {
    fn cmp(&self, other: &tree::IteratorResult<'a, T>) -> Ordering {
        self.count.cmp(&other.count).reverse()
    }
}

impl<'a, T: Ord + 'a> PartialOrd for tree::IteratorResult<'a, T> {
    fn partial_cmp(&self, other: &tree::IteratorResult<'a, T>) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl<'a, T: Ord + 'a> PartialEq for tree::IteratorResult<'a, T> {
    fn eq(&self, other: &tree::IteratorResult<'a, T>) -> bool {
        self.count == other.count
    }
}

fn main() {
    let stdin = std::io::stdin();
    let mut binary_tree = tree::Tree::new();
    let word_pattern = Regex::new(r"\w+").unwrap();

    for line in stdin.lock().lines() {
        let line = line.unwrap();

        for cap in word_pattern.captures_iter(line.as_str()) {
            let word = String::from(&cap[0]);
            binary_tree.insert(word);
        }
    }

    let mut top10 = top::Top::new(10);

    for val in binary_tree.iter() {
        top10.insert(val);
    }
    print!("top10 [");
    for val in top10.vec.iter() {
        print!("{}, ", val);
    }
    println!("]");
}
