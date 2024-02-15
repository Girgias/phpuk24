/* rationals extension for PHP (c) 2024 Gina Banyard */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_rationals.h"
#include "rationals_arginfo.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

static zend_class_entry *zend_ce_rational_number;
static zend_object_handlers rational_object_handlers;

/* {{{ void test1() */
PHP_FUNCTION(test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "rationals");
}
/* }}} */

/* {{{ string test2( [ string $var ] ) */
PHP_FUNCTION(test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

PHP_METHOD(RationalNumber, __construct)
{
	zend_long numerator;
	zend_long denominator;
	zval *this_z = ZEND_THIS;
	zend_object *this_obj = Z_OBJ_P(this_z);

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(numerator)
		Z_PARAM_LONG(denominator)
	ZEND_PARSE_PARAMETERS_END();

	if (denominator == 0) {
		zend_argument_value_error(2, "cannot be 0");
		RETURN_THROWS();
	}

	zend_update_property_long(zend_ce_rational_number, this_obj, "numerator", strlen("numerator"), numerator);
	zend_update_property_long(zend_ce_rational_number, this_obj, "denominator", strlen("denominator"), denominator);
}

static void rational_add_objects(zval *return_value, zend_object *op1, zend_object *op2)
{
	zend_long n1 = Z_LVAL_P(OBJ_PROP_NUM(op1, 0));
	zend_long d1 = Z_LVAL_P(OBJ_PROP_NUM(op1, 1));
	zend_long n2 = Z_LVAL_P(OBJ_PROP_NUM(op2, 0));
	zend_long d2 = Z_LVAL_P(OBJ_PROP_NUM(op2, 1));

	zend_long nr = n1 * d2 + n2 * d1;
	zend_long dr = d1 * d2;


	ZVAL_LONG(OBJ_PROP_NUM(Z_OBJ_P(return_value), 0), nr);
	ZVAL_LONG(OBJ_PROP_NUM(Z_OBJ_P(return_value), 1), dr);
}


PHP_METHOD(RationalNumber, add)
{
	zval *this_z = ZEND_THIS;
	zend_object *this_obj = Z_OBJ_P(this_z);
	zend_object *other_obj = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(other_obj, zend_ce_rational_number)
	ZEND_PARSE_PARAMETERS_END();

	object_init_ex(return_value, zend_ce_rational_number);
	rational_add_objects(return_value, this_obj, other_obj);
}

static void rational_sub_objects(zval *return_value, zend_object *op1, zend_object *op2)
{
	zend_long n1 = Z_LVAL_P(OBJ_PROP_NUM(op1, 0));
	zend_long d1 = Z_LVAL_P(OBJ_PROP_NUM(op1, 1));
	zend_long n2 = Z_LVAL_P(OBJ_PROP_NUM(op2, 0));
	zend_long d2 = Z_LVAL_P(OBJ_PROP_NUM(op2, 1));

	zend_long nr = n1 * d2 - n2 * d1;
	zend_long dr = d1 * d2;


	ZVAL_LONG(OBJ_PROP_NUM(Z_OBJ_P(return_value), 0), nr);
	ZVAL_LONG(OBJ_PROP_NUM(Z_OBJ_P(return_value), 1), dr);
}

static zend_result rational_do_operation(uint8_t opcode, zval *result, zval *op1, zval *op2)
{
	zend_result retval = SUCCESS;
	zval op1_copy;
	if (result == op1) {
		ZVAL_COPY_VALUE(&op1_copy, op1);
		op1 = &op1_copy;
	}
	
	switch(opcode) {
		case ZEND_ADD:
			object_init_ex(result, zend_ce_rational_number);
			rational_add_objects(result, Z_OBJ_P(op1), Z_OBJ_P(op2));
			break;
		default:
			retval = FAILURE;
	}
	//retval = gmp_do_operation_ex(opcode, result, op1, op2);
		
	if (retval == SUCCESS && op1 == &op1_copy) {
		zval_ptr_dtor(op1);
	}

	return retval;
}

static zend_long gcd(zend_long op1, zend_long op2)
{
	return (op1 % op2) ? gcd(op2, op1 % op2) : op2;
}

static void normalise_rationals(zend_object *obj)
{
	zend_long n = Z_LVAL_P(OBJ_PROP_NUM(obj, 0));
	zend_long d = Z_LVAL_P(OBJ_PROP_NUM(obj, 1));

	zend_long divide_by = gcd(n, d);
	zend_long new_n = n/divide_by;
	zend_long new_d = d/divide_by;

	if (new_d < 0) {
		new_n *= -1;
		new_d *= -1;
	}

	ZVAL_LONG(OBJ_PROP_NUM(obj, 0), new_n);
	ZVAL_LONG(OBJ_PROP_NUM(obj, 1), new_d);
}


PHP_METHOD(RationalNumber, normalise)
{
	zval *this_z = ZEND_THIS;
	zend_object *this_obj = Z_OBJ_P(this_z);

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

	normalise_rationals(this_obj);
}

PHP_METHOD(RationalNumber, cmp)
{
	zval *this_z = ZEND_THIS;
	zend_object *this_obj = Z_OBJ_P(this_z);
	zend_object *other_obj = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(other_obj, zend_ce_rational_number)
	ZEND_PARSE_PARAMETERS_END();

	zval tmp;
	object_init_ex(&tmp, zend_ce_rational_number);
	rational_sub_objects(&tmp, this_obj, other_obj);

	RETVAL_COPY(OBJ_PROP_NUM(Z_OBJ(tmp), 0));

	zval_ptr_dtor(&tmp);
}

static int rational_compare(zval *op1, zval *op2)
{
	zval tmp;
	object_init_ex(&tmp, zend_ce_rational_number);
	rational_sub_objects(&tmp, Z_OBJ_P(op1), Z_OBJ_P(op2));

	zend_long result = Z_LVAL_P(OBJ_PROP_NUM(Z_OBJ(tmp), 0));

	zval_ptr_dtor(&tmp);

	return result;
}

PHP_MINIT_FUNCTION(rationals)
{
	zend_ce_rational_number = register_class_RationalNumber();
	zend_ce_rational_number->default_object_handlers = &rational_object_handlers;
	memcpy(&rational_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	rational_object_handlers.do_operation = rational_do_operation;
	rational_object_handlers.compare = rational_compare;
	return SUCCESS;
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(rationals)
{
#if defined(ZTS) && defined(COMPILE_DL_RATIONALS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(rationals)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "rationals support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ rationals_module_entry */
zend_module_entry rationals_module_entry = {
	STANDARD_MODULE_HEADER,
	"rationals",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	PHP_MINIT(rationals),			/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(rationals),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(rationals),			/* PHP_MINFO - Module info */
	PHP_RATIONALS_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_RATIONALS
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(rationals)
#endif
