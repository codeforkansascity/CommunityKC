
/**
 * @file
 * Drupal to Google Maps Geocoder.
 */

(function($){
  Drupal.behaviors.term_gmap = {
    attach: function (context, settings) {
         var geocoder;
         var map;
         geocoder = new google.maps.Geocoder();
         var address = Drupal.settings.term_gmap.title;
         geocoder.geocode({ 'address': address}, function(results, status) {
           if (status == google.maps.GeocoderStatus.OK) {
             var mapOptions = {
             zoom: 8,
             mapTypeId: google.maps.MapTypeId.ROADMAP
             }
           map = new google.maps.Map(document.getElementById('map_canvas'), mapOptions);
           map.setCenter(results[0].geometry.location);
           var marker = new google.maps.Marker({
             map: map,
             position: results[0].geometry.location
             });
           }
           else {
             $('#map_canvas').html("Google returned zero results. Click below links to view default map.");
           }
         });
   }
  };
})(jQuery);
