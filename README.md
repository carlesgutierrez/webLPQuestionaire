# webLPQuestionaire

This is a simple App (TokensMatters App) that manage to edit a formularie of questions in a local database and an "interactive App" that promtp questions from server and play a quesionaire with them.


# Installation

First, pick the branch that matches your version of openFrameworks:

* OF [stable](https://github.com/openframeworks/openFrameworks/tree/stable) (0.9.8): use [ofxCv/stable](https://github.com/kylemcdonald/ofxCv/tree/stable)

Either clone out the source code using git:

	> cd openFrameworks/apps/
	> git clone https://github.com/....

Or download the source from my GitHub [here](https://github.com/kylemcdonald/ofxCv/archive/master.zip), unzip the folder and place it in your `openFrameworks/app` folder.


# Usage

Manage data questions with Firefox 
Tip( Refresh your WebBrowser fisrt Time with Shift Key Pressed ) if you apply changes in the website. 


Cross platform.  Use projectGenerator to create the project. All Addons used are crossplatform.

Check allways your branch before download them. If there is a **Stable** verion, use it, is ready for stable release OF-->0.98. 

# External addons

- https://github.com/jvcleave/ofxImGui
- https://github.com/arturoc/ofxEasing
- https://github.com/jeffcrouse/ofxJSON (master)

**https://github.com/bakercp/ofxSQLiteCpp**(stable)
For VS2015 there is a problem with projectGenerator. So solve it : Each time has been generated a new project it's necesary to edit properties of file **sqlite3**(ofxSQLiteCpp\libs\SQLiteCpp\sqlite3) and set **compile as C code** and **No Common Language RunTime Support**. 

- +info and screenshots at OF forum -->  https://github.com/bakercp/ofxSQLiteCpp/issues/7

**https://github.com/carlesgutierrez/ofxThreadedImage** (master)
ofxThreadedImage Requires:
- https://github.com/armadillu/ofxSimpleHttp (master)


**https://github.com/bakercp/ofxJSONRPC**(stable)
ofxJSONRPC requires:
- [https://github.com/bakercp/ofxHTTP (stable)

-   [https://github.com/bakercp/ofxIO (stable)
-   [https://github.com/bakercp/ofxMediaType (stable)
-   [https://github.com/bakercp/ofxSSLManager (stable)
-   [https://github.com/bakercp/ofxNetworkUtils (stable)
-  https://github.com/bakercp/ofxTaskQueue/ (stable)

