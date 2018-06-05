<?php

class UtilHelper {

  /**
   * Registers a unique function call for execution on shutdown.
   *
   * Wrapper for drupal_register_shutdown_function() that does not add the
   * function call if it already exists in the shutdown function stack.
   *
   * @param callable $callback
   *   The shutdown function to register.
   * @param ...
   *   Additional arguments to pass to the shutdown function.
   *
   * @return bool
   *   TRUE if the function was added, or FALSE if it was already in the stack.
   *
   * @see drupal_register_shutdown_function()
   */
  public static function registerUniqueShutdownFunction($callback = NULL) {
    $args = func_get_args();
    array_shift($args);

    $existing_callbacks = drupal_register_shutdown_function();
    foreach ($existing_callbacks as $existing_callback) {
      if ($existing_callback['callback'] === $callback && $existing_callback['arguments'] === $args) {
        return FALSE;
      }
    }

    array_unshift($args, $callback);
    call_user_func_array('drupal_register_shutdown_function', $args);
    return TRUE;
  }

}
