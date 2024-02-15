/* rationals extension for PHP (c) 2024 Gina Banyard */

#ifndef PHP_RATIONALS_H
# define PHP_RATIONALS_H

extern zend_module_entry rationals_module_entry;
# define phpext_rationals_ptr &rationals_module_entry

# define PHP_RATIONALS_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_RATIONALS)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_RATIONALS_H */
