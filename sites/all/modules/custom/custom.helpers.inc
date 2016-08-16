<?php

function _custom_decimal_prefs_to_bit_array($dec_val) {
	$bits = str_pad(decbin($dec_val),3,'0',STR_PAD_LEFT);
	$bit_array = str_split($bits);
	return $bit_array;
}
