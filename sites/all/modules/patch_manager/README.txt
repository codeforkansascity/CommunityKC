
Patch manager provides a developer tool for managing patches
to core and contributed modules.


CONTENTS OF THIS FILE
---------------------

 * About the developer
 * Requirements
 * Patch naming
 * Configuration
 * More Information

ABOUT THE DEVELOPER
-------------------

Initial development (D6 version) was made by the user aidanlis.
Port to D7 was made by the user Staratel.

Hello all! I am Staratel, my name is Dmitry Danilson.
I am a freelance web developer.
My goal is to revolutionize the open-source world.
How? Find the way to monetize open-source projects appropriately.
What does it mean? It means that such ways as
- asking for donations
- contextual links and advertising
ARE NOT the way we should do it.
Money - is the only thing that is missing by open-source projects
to conquer the whole world! :)

That's why I (while doing paid orders) am working on project that 
will provide this opportunity.
To finish it I need at least two things:
1) Greater developer skills : this aim inspired me to make this porting.
I develop my developer skills - and got the tool that helps me to do it
even more faster.
2) Dream team : what else I really need - is a couple of man (if more - not 
a problem) that are also interested of open-source future.
If you think that this is amazing theme to work on
or you have suggestions 
or you are interested what is the project I am working on 
or even just have some kind words to say 
- please feel free to write an email to me : kupifoto@gmail.com .
Thank you for reading!

REQUIREMENTS
------------

The patch_manager module requires the following modules:
  views
  file
  views_bulk_operations

It helps to have a working patch binary on your system that
is executable by the webserver user.


PATCH NAMING
------------

If you have filefield_paths installed (with token, and pathauto),
this will allow you to automatically rename patch files. The
Drupal suggested naming scheme is:
  module-description-issue-comment.patch

With tokens, this would be:
  [field_module-raw]-[title]-[field_drupal_issue-raw].patch
  
You can set this up here:
  /admin/structure/types/manage/patch/fields/field_patch


CONFIGURATION
-------------

Access the configuration page to set the path to your patch
binary. This will allow you to patch and reverse patches through
the administration interface.
  /admin/structure/patch

You can start adding patches immediately, as you would a normal node:
  /node/add/patch

You can modify the default fields to store extra information via
the content module:
  /admin/structure/types/manage/patch/fields
  
Everything is powered by Views, so you can modify or create new views:
  /admin/structure/views/view/patches/edit

MORE INFORMATION
----------------

See the project page at:
  http://drupal.org/project/patch_manager

