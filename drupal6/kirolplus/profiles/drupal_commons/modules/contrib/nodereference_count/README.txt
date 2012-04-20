$Id: README.txt,v 1.1.2.1 2010/04/13 05:39:38 gilgabar Exp $

Nodereference Count
-------------------

This is a CCK field type that will count the number of nodereferences to a 
particular node.  The count is updated both when the node that is being counted 
is saved, as well as when a node that is referencing the node being counted is 
saved, updated or deleted.  It will count references from individual 
nodereference fields as well as aggregate counts from multiple nodereference 
fields to the same node.

This should be an improvement over alternate solutions to the same problem, 
such as: 
Using a computed field, which would either be updated when viewed, but not 
available to views, or when saved, but not when a nodereference was added or 
removed.  Or a view, which would be updated when displayed, but with a 
performance price and not be available within the node itself.

Installation
------------

Copy nodereference_count to your module directory and then enable on the admin
modules page.  Be sure you have at least one nodereference field configured and 
then add a nodereference count field to a content type that is referenced by a 
nodereference.  Check the boxes for the nodereference fields that should be 
counted.  You will need to re-save any existing nodes or their referencing nodes 
in order to update the count.

Updating counts for pre-existing nodereferences
-----------------------------------------------
While the nodereference count fields will be updated when the node is saved or when the referencing node is saved, that isn't much help for pre-existing nodereferences to nodes created prior to the addition of a nodereference count field.  The Views Bulk Operations (VBO) module, http://drupal.org/project/views_bulk_operations, is the recommended solution .  Using VBO you can re-save all of the nodes that have a nodereference_count field.  That will update the count for each of those nodes.  The specifics will vary for each site, but the general instructions for doing this with VBO are as follows:

  - Install the Views and VBO modules if you do not already have them installed.
  - Go to /admin/build/views/add and create a new node view.
  - Create a new page display.
  - Change the style from Unformatted to Bulk Operations.
  - Select 'Use Batch API' under TO EXECUTE OPERATIONS.
  - Check 'Save post (node_save_action)' under SELECTED OPERATIONS.
  - Click 'Update default display'.
  - Add a path under Page Settings.
  - Add 'Node: Title' under Fields.
  - Add 'Node: Type' under Filters.  Be sure to select the node types that contain nodereference_count fields.
  - Save the view.
  - Visit the path that you set for the view.
  - Select all the nodes.
  - Click 'Save post'.  
  - Your nodereference_count fields should now be updated.
  - You are unlikely to need to use the view again, so feel free to delete it if you like.

Author
------
Brendan Andersen
brendan@omnifik.com