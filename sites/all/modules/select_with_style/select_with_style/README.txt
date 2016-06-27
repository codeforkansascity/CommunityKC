
SELECT WITH STYLE
=================

This module allows you to attractively style select lists, in particular those
that feature parent/child hierarchies, like taxonomies. The module adds CSS
classes that reflect family names and depths in the hierarchy, so you can render
one family differently from another and different from their children. You can
apply colours, font styles or even images, like country flags.

A few basic .css files have been provided to get you started. You can select
these when you configure the widget. E.g. "Plain Jane - blue.css" or "flags.css"
You can add your own CSS, either via your theme's style.css or in a separate
.css file, which you place in a directory you declare on the Select with Style
configuration page.

You can also set the height of select boxes and may use any hierarchy depth
indicator prefix string instead of core's '-'.

All of the above is achieved through two new variants of the classic "Select
list" widget. Both variants are on offer when you select a widget for a field
of type term reference. The new widgets are:
- Select list, styled optgroups
- Select list, styled tree

Once assigned to a field, the same widget will automatically appear in Views
when you add an exposed filter, unless you unticked the associated box on the
module configuration page. Or if you want the widget to appear in Views
ONLY (and not when editing an entity), then you can use the global settings on
the module configuration page to configure Views exposed filter widgets.

Just to make that even clearer, here are the steps for the Select with Style
widget. After you have attached your Select with Style widget to a taxonomy
field under the "Manage fields" tab of the node or other entity type, go to your
Views console and press add in the "Filter criteria" section. Pick the Views
field in question. Do not pick "Content: Has taxonomy term(s)". On the next
panel select "Dropdown" rather than "Autocomplete" and tick the "Show hierarchy
in dropdown" box, if so desired (recommended). Then, after "Apply", on the next
panel tick the box "Expose this filter to visitors...". The exposed filter
should automatically render in the same widget style as used on the content
Edit form, thus creating a consistent look throughout your site. This also works
for filters that are exposed in a block (one of the advanced options on the
right hand side in the Views UI). Note that for an exposed filter to show up in
a block, AJAX must be set to Yes on the View. Be aware that ticking "Allow
multiple selections" on the filter configuration panel results in a multi-select
box, which renders differently from a single-select.

The two widgets are similar in appearance, but different in functionality. In
the styled optgroups parent options become labels, which cannot be selected
(clicked), whereas in the styled tree the parents are selectable options, just
like the children. Another difference between the styled optgroups and the
styled tree is that due to W3C/browser restrictions optgroups only go one level
deep, whereas trees can be nested as deep as your taxonomy dictates.

By the way, the definition of a parent is any item that is not a leaf.

These widgets are lightweight, javascript-free solutions without dependencies.
No libraries are required. There are no module configurations. Just enable the
module and select or tweak your CSS.

CSS classes added for a parent label or option are of this format:

  class="option-parent group-PARENT tid-NUMBER depth-0"

CSS classes added for a child option are of this format:

  class="option-child group-PARENT tid-NUMBER depth-2"

Where PARENT is the name of the parent taxonomy term and NUMBER the id of the
option term.

HOW TO CREATE A COUNTRY & CITY DROP-DOWN WITH FLAG IMAGES?
Create a city vocabulary at Structure >> Taxonomy. Add terms for cities and
countries in any order. Then use the handles to drag cities under their parent
countries and indent them to make them children. Use the official country names,
in the language of your site. With the city vocabulary saved, click the "Manage
fields" tab of a content type. Under the "Add a new field" heading choose the
field type Term Reference and team it up with either the "Select list, styled
tree" or "Select list, styled optgroup" widgets. Press Save and Save again to
arrive at the field Edit tab. Here you can specify additional parameters
pertaining to Select with Style. The important one for this use-case is the
transformation callback. Enter "select_with_style_country_name_to_code" and
Save. The final step is to select the flags.css file from the "Styling file(s)"
select box. That should do it. Works in Firefox, not yet supported by Chrome and
Safari.

Finally, while the main "Select with Style" functionality does not require any
javascript, you may choose to add some additional special effects. See
select_with_style.js


HTML/CSS DISCLAIMER:
Anno 2014 browser support for select lists is still so-so. Firefox is generally
great, but Chrome and Safari do not honour all of the attributes that are
standard on other HTML elements. This is especially so for single-choice
drop-downs.


INVITE FOR FUTURE EXTENSION:
Someone to create a widget to make general lists other than taxonomies
hierarchical, maybe using indentation to denote an item is a child of the
preceding item:

1|parent1
  11|child_a
  49|child_b
5|parent2
  66|child_c
  ...
...

APPENDIX
While the main "Select with Style" functionality does not require any
javascript, you may choose to add some additional effects. Below are a few
ideas. Put the one you like in select_with_style.js
These behaviors are attached to the entire page. When the document is ready
all of the attach functions below are called, passing in the document context
and the value of Drupal.settings.

(function($) {

  // #1 Put a green border around select lists, text fields and text areas, the
  //    moment an option is clicked or a value entered.
  Drupal.behaviors.select_with_style_color_border_on_select = {
    attach: function(context, settings) {
      $(":input, :checkbox", context).change(function() { // can't seem to style checkboxes
        this.style.border = "2px solid #5ed230";
      });
    }
  }

  // #2 Render select as small box initially. Then expand the select box
  //    to reveal all its options when the box is hovered over.
  Drupal.behaviors.select_with_style_expand_on_hover = {
    attach: function(context, settings) {
      $("select", context).mouseover(function() {
        this.size = this.options.length;
      });
      $("select").mouseout(function() {
        this.size = 1;
      });
    }
  }

})(jQuery);