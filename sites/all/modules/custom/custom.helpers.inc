<?php

function _custom_decimal_prefs_to_bit_array($dec_val) {
	$bits = str_pad(decbin($dec_val),3,'0',STR_PAD_LEFT);
	$bit_array = str_split($bits);
	return $bit_array;
}


/**
 * Safely gets a dynamic field value from the node
 * @param stdClass $node - populated node object
 * @param string $fieldname - name of field property in node ex. field_firstname
 * @param string $lang - language, usually LANGUAGE_NONE which is 'und'
 * @param string $delta - for fields with multiple values this number increments each value, otherwise 0
 * @param string $key - name of assoc array key that holds field value. usually 'value' but sometimes other words like 'email'
 * @return string value from that field or ''
 */
function _custom_safe_get_field($node, $fieldname, $lang = LANGUAGE_NONE, $delta = 0, $key = 'value') {
	if (property_exists($node, $fieldname)) {
		# get property from node using var
		$field = $node->$fieldname;
		# now only deal with the regular field array
		if (array_key_exists($lang, $field)
		    && array_key_exists($delta, $field[$lang])
		    && array_key_exists($key, $field[$lang][$delta])
		) {
			return $field[$lang][$delta][$key];
		}
		else {
			return '';
		}
	}
	else {
		return '';
	}
}