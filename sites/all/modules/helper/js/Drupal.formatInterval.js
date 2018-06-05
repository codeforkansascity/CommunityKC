(function ($) {

  "use strict";

  /**
   * Formats a time interval with the requested granularity.
   *
   * @param {Number} interval
   *   The length of the interval in seconds.
   * @param {Number} granularity
   *   How many different units to display in the string.
   * @param {Object} options
   *   The options to pass to the Drupal.t() function.
   *
   * @return {String}
   *   A translated string representation of the interval.
   */
  Drupal.formatInterval = function(interval, granularity, options) {
    granularity = granularity || 2;
    options = options || {};

    var units = {
      '1 year|@count years': 31536000,
      '1 month|@count months': 2592000,
      '1 week|@count weeks': 604800,
      '1 day|@count days': 86400,
      '1 hour|@count hours': 3600,
      '1 min|@count min': 60,
      '1 sec|@count sec': 1
    };
    var output = '';

    for (var key in units) {
      var keys = key.split('|');
      var value = units[key];
      if (interval >= value) {
        output += (output.length ? ' ' : '') + Drupal.formatPlural(Math.floor(interval / value), keys[0], keys[1], {}, options);
        interval %= value;
        granularity--;
      }

      if (granularity == 0) {
        break;
      }
    }

    return output.length ? output : Drupal.t('0 sec', {}, options);
  }

})(jQuery);
