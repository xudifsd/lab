pub struct Top<T: Ord> {
    size: usize,
    pub vec: Vec<T>,
}

impl<T: Ord> Top<T> {
    pub fn new(size: usize) -> Top<T> {
        Top { size: size, vec: Vec::new() }
    }

    pub fn insert(&mut self, val: T) {
        match self.vec.binary_search(&val) {
            Ok(index) => {
                self.vec.insert(index, val);
            }
            Err(index) => {
                self.vec.insert(index, val);
            }
        }
        if self.vec.len() > self.size {
            self.vec.pop();
        }
    }
}
