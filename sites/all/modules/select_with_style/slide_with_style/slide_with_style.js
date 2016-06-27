/**
 * @file
 * Javascript for "Slide with Style" module
 *
 * Most of this was gratefully copied from the SliderField module then modified
 * and extended to implement additional features.
 * Depends on jQueryUI library, included with core at misc/ui/jquery.ui.slider
 *
 * @see http://jqueryui.com/slider/#range
 */
(function ($) {
  Drupal.behaviors.slide_with_style_attach = {

    attach: function(context, settings) {

      $('.edit-slide-with-style-slider', context).each(function() {
        var textField = $(this);
        var slider = textField.closest('div').parent().find('.slide-with-style-slider');
        if (!slider || slider.slider === undefined) {
          // May happen if there's a JS error earlier on the page (eg toolbar.js)
          return;
        }

        var id = textField.attr('id');

        // There will be one array of slider parameters for each slider field.
        var pars = settings.slider;
        if (pars[id] === undefined) { // Slider requested for inappropriate form field
          return;
        }
        if (pars[id].range === true) {
          textField.attr('readonly', 'readonly'); // no editable field support for range slider
          pars[id].values = pars[id].values.slice(0, 2);
        }
        else if (typeof pars[id].value === 'object') {
          // Defensive programming. May happen with profile2.
          pars[id].value = parseFloat(pars[id].value.value === '' ? pars[id].min : pars[id].value.value);
        }
        slider.slider({
          animate    : true,
          orientation: pars[id].orientation, // 'horizontal' or 'vertical'
          range      : pars[id].range, // 'min', 'max', true or false
          step       : parseFloat(pars[id].step),
          min        : parseFloat(pars[id].min),
          max        : parseFloat(pars[id].max),
          value      : pars[id].range === true ? null : pars[id].value, // single value
          values     : pars[id].range === true ? pars[id].values : null,// range

          create: function(event, ui) {
            if (!pars[id].textfield) {
              textField.hide();
              textField.prev('span.field-prefix').hide();
              textField.next('span.field-suffix').hide();
            }
            if (pars[id].bubble) {
              if (pars[id].range === true) { // as opposed to 'min' or false
                var t0 = pars[id].textvalues ? pars[id].textvalues[pars[id].values[0]] : pars[id].values[0];
                var bubble0 = $('<div class="slider-bubble bubble-' + id + '">' + t0 + '</div>');
                $(this).find('.ui-slider-handle').first().append(bubble0);
                var t1 = pars[id].textvalues ? pars[id].textvalues[pars[id].values[1]] : pars[id].values[1];
                var bubble1 = $('<div class="slider-bubble bubble-' + id + '">' + t1 + '</div>');
                $(this).find('.ui-slider-handle').last().append(bubble1);
              }
              else {
                var t = pars[id].textvalues ? pars[id].textvalues[pars[id].value] : pars[id].value;
                var bubble = $('<div class="slider-bubble bubble-' + id + '">' + t + '</div>');
                $(this).find('.ui-slider-handle').append(bubble);
              }
            }
          },
          // Callback to update the value in the textfield and bubble when slider is moved.
          slide: function(event, ui) {
            var t = (pars[id].range === true) ? (ui.values[0] + '--' + ui.values[1]) : ui.value;
            // Cannot put list value in textField as it would submit list value rather than list key.
            // As list keys have little meaning to humans, pars.textfield==false is recommended for lists.
            $('#' + textField.attr('id')).val(t);
            if (pars[id].bubble) {
              ui.handle.childNodes[0].innerHTML = pars[id].textvalues ? pars[id].textvalues[ui.value] : ui.value;
            }
          },
          stop: function(event, ui) {
            if (pars[id].autosubmit) {
              $(this).parents('form').submit();
            }
          }
        });

        // Adjust slider and bubble text when the textfield value is changed.
        textField.bind('keyup', function(event) {
          if (pars[id].bubble) {
            $('.bubble-' + id)[0].innerHTML = pars[id].textvalues
               ? pars[id].textvalues[textField.val()]
               : textField.val();
          }
          setTimeout(function() {
            slider.slider('value', parseFloat(textField.val()));
          }, 0);
        });

      });
    }
  };
})(jQuery);
