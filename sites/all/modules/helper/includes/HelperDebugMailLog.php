<?php

/**
 * Provides a mail system class useful for debugging mail output.
 *
 * Usage in settings.php:
 * @code
 * $conf['mail_system']['default-system'] = 'HelperDebugMailLog';
 * @endcode
 */
class HelperDebugMailLog extends DefaultMailSystem {

  /**
   * Overrides DefaultMailSystem::mail().
   *
   * Accepts an e-mail message and displays it on screen, and additionally logs
   * it to watchdog().
   */
  public function mail(array $message) {
    $header = "To: {$message['to']} <br />Subject: {$message['subject']}";
    $string = check_plain(print_r($message, TRUE));
    $string = '<pre>' . $string . '</pre>';

    if (module_exists('devel')) {
      dpm($message, $header);
    }
    else {
      drupal_set_message($header . ' ' . $string);
    }

    // Don't actually use debug to display the message since we want to be able
    // to categorize the watchdog type as 'mail' so it can be filterable in
    // UI.
    watchdog('mail', $header . ' ' . $string, NULL, WATCHDOG_INFO);

    return TRUE;
  }
}
