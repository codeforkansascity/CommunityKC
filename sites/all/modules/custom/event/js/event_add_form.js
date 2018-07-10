(function ($) {
  Drupal.behaviors.customEventAutocompleteSupervisor = {
    attach: function (context, settings) {
      $('#edit-field-project-und', context).bind('autocompleteSelect', function(event, node) {
        // Adds auto fill to the project address fields when a related project is selected.
        // if country is on none it won't work so well
        var project_id = 0;
        var find_id_regex = /^.*?\((\d*)\)$/;
        var fieldValue = $('#edit-field-project-und').val();
        var match = fieldValue.match(find_id_regex);
        if (match.length > 1) {
          project_id = match[1];
          var address = $.get('/project/' + project_id + '/address-lookup', null,
          function(response) {
              /* address json response example:
                {
                  "country": "US",
                  "administrative_area": "MO",
                  "sub_administrative_area": null,
                  "locality": "Kansas City",
                  "dependent_locality": null,
                  "postal_code": "",
                  "thoroughfare": "53rd to 63rd Swope Parkway to Elmwood",
                  "premise": null,
                  "sub_premise": null,
                  "organisation_name": null,
                  "name_line": null,
                  "first_name": null,
                  "last_name": null,
                  "data": null
                }
              */
              $('#edit-field-location-und-0-country--2').val(response.country).change();
              $('#edit-field-location-und-0-thoroughfare').val(response.thoroughfare); // address
              $('#edit-field-location-und-0-premise').val(response.premise); // address 2
              $('#edit-field-location-und-0-locality').val(response.locality); // city
              $('#edit-field-location-und-0-administrative-area').val(response.adminisrtative_area); // state
              $('#edit-field-location-und-0-postal-code').val(response.postal_code); // zip code
          });
        }
      });
    }
  };

}(jQuery));
