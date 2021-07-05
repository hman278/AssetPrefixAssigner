<h3>About:</h3> 
This plugin lets you assign correct prefixes to all your assets in one click
The styling was borrowed from https://github.com/Allar/ue4-style-guide (See below for more information)

<h3>How to use:</h3>
Clone the repository to your project's Plugin folder, reopen the editor,
go to Edit->Plugins, find the plugin, enable it then restart the editor.
Now go to Window->AssetPrefixAssigner. Boom, you now have correctly prefixed assets.

If you ever want to add more supported asset types simply navigate to the plugin's
Resources folder. There you can see two json files. All the blueprint types must be 
defined in BlueprintAssetProperties.json file (i.e. AIController), the rest should be defined in AssetProperties.json.

<h3>IMPORTANT!!!</h3>
You must ensure that your Content folders contents are all NOT read only, otherwise the plugin will not function properly.
If you use version control software like Perforce, make sure that all the assets that you want renamed are checked out, otherwise the plugin may not work.

That's it, have fun:)
