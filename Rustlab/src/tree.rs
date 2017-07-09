use std::boxed::Box;

pub struct Tree<T: Ord> {
    root: Option<TreeNode<T>>
}

impl<T: Ord> Tree<T> {
    pub fn new() -> Tree<T> {
        Tree { root: None }
    }

    pub fn insert(&mut self, value: T) {
        match self.root {
            None => { self.root = Some(TreeNode::new(value)); }
            Some(ref mut root) => { root.insert(value); }
        }
    }

    pub fn iter(&self) -> TreeIterator<T> {
        match self.root {
            None => { TreeIterator::empty() }
            Some(ref root) => { TreeIterator::new(root) }
        }
    }
}

struct TreeNode<T: Ord> {
    value: T,
    count: usize,
    left:  Option<Box<TreeNode<T>>>,
    right: Option<Box<TreeNode<T>>>,
}

impl<T: Ord> TreeNode<T> {
    fn new(value: T) -> TreeNode<T> {
        TreeNode {
            value: value,
            count: 1,
            left:  None,
            right: None
        }
    }

    fn insert(&mut self, value: T) {
        if value < self.value {
            match self.left {
                None => {
                    self.left = Some(Box::new(TreeNode::new(value)));
                }
                Some(ref mut left_node) => {
                    left_node.insert(value);
                }
            }
        } else if value > self.value {
            match self.right {
                None => {
                    self.right = Some(Box::new(TreeNode::new(value)));
                }
                Some(ref mut right_node) => {
                    right_node.insert(value);
                }
            }
        } else {
            self.count += 1;
        }
    }
}

pub struct TreeIterator<'a, T: Ord + 'a> {
    stack: Vec<&'a TreeNode<T>>,
}

impl<'a, T: Ord + 'a> TreeIterator<'a, T> {
    fn empty() -> TreeIterator<'a, T> {
        TreeIterator { stack: Vec::new() }
    }

    fn new(value: &'a TreeNode<T>) -> TreeIterator<'a, T> {
        let mut result = TreeIterator { stack: Vec::new() };

        result.into_stack(value);

        result
    }

    fn into_stack(&mut self, node: &'a TreeNode<T>) {
        let mut left_most = node;
        loop {
            self.stack.push(left_most);

            match left_most.left {
                None => { break; }
                Some(ref node) => { left_most = node; }
            }
        }
    }
}

#[derive(Eq)]
pub struct IteratorResult<'a, T: Ord + 'a> {
    pub value: &'a T,
    pub count: usize,
}

impl<'a, T: Ord + 'a> Iterator for TreeIterator<'a, T> {
    type Item = IteratorResult<'a, T>;

    fn next(&mut self) -> Option<Self::Item> {
        let top = self.stack.pop();
        match top {
            None => { None }
            Some(ref node) => {
                let result = Some(IteratorResult { value: &node.value, count: node.count });
                match node.right {
                    None => {}
                    Some(ref node) => { self.into_stack(node); }
                }
                result
            }
        }
    }
}
