(defmacro ->> (x &rest form)
  (labels ((list-if-not (x)
                        (if (listp x)
                            x
                          (list x))))
    (if (null (car form))
        x
      `(->> ,(append (list-if-not (car form))
                     (list x))
        ,@(cdr form)))))

(defun filter (fun lst)
 (labels ((iter (acc l)
           (if (null l)
            acc
            (iter (if (funcall fun (car l))
                   (cons (car l) acc)
                   acc)
             (cdr l)))))
  (iter '() lst)))

(->> '(2 3 2 1) (filter #'oddp) print)
