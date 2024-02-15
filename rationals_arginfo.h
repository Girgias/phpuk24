/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: ddfda0e3a5ee3547714b399386c0bc06225f31ff */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_test1, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_test2, 0, 0, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, str, IS_STRING, 0, "\"\"")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_RationalNumber___construct, 0, 0, 2)
	ZEND_ARG_TYPE_INFO(0, numerator, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, denominator, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_RationalNumber_add, 0, 1, RationalNumber, 0)
	ZEND_ARG_OBJ_INFO(0, o, RationalNumber, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_RationalNumber_normalise arginfo_test1

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_RationalNumber_cmp, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, o, RationalNumber, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(test1);
ZEND_FUNCTION(test2);
ZEND_METHOD(RationalNumber, __construct);
ZEND_METHOD(RationalNumber, add);
ZEND_METHOD(RationalNumber, normalise);
ZEND_METHOD(RationalNumber, cmp);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(test1, arginfo_test1)
	ZEND_FE(test2, arginfo_test2)
	ZEND_FE_END
};


static const zend_function_entry class_RationalNumber_methods[] = {
	ZEND_ME(RationalNumber, __construct, arginfo_class_RationalNumber___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(RationalNumber, add, arginfo_class_RationalNumber_add, ZEND_ACC_PUBLIC)
	ZEND_ME(RationalNumber, normalise, arginfo_class_RationalNumber_normalise, ZEND_ACC_PUBLIC)
	ZEND_ME(RationalNumber, cmp, arginfo_class_RationalNumber_cmp, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_RationalNumber(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "RationalNumber", class_RationalNumber_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);

	zval property_numerator_default_value;
	ZVAL_UNDEF(&property_numerator_default_value);
	zend_string *property_numerator_name = zend_string_init("numerator", sizeof("numerator") - 1, 1);
	zend_declare_typed_property(class_entry, property_numerator_name, &property_numerator_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_numerator_name);

	zval property_denominator_default_value;
	ZVAL_UNDEF(&property_denominator_default_value);
	zend_string *property_denominator_name = zend_string_init("denominator", sizeof("denominator") - 1, 1);
	zend_declare_typed_property(class_entry, property_denominator_name, &property_denominator_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_denominator_name);

	return class_entry;
}
