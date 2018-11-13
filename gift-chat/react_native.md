React Native
===========

## Starting React Native  

You will need `React Native` development environment for this tutorial.  
[React Native docs](http://facebook.github.io/react-native/docs/getting-started.html#content) will help you set up development environment.  
This tutorial is based on OS X.  

1. Install [Node.js](https://nodejs.org/en/) 4.0 or newer.  
2. Install [watchman](https://facebook.github.io/watchman/docs/install.html).  
3. Install [React Native](http://facebook.github.io/react-native/)  
  
```unix  
   $ npm install -g react-native-cli  
```  

3. Install [atom](https://atom.io/)  
 - Atom is a wonderful text editor. But, if you want to use other editor, it is okay.    


## Create React Native Application  
Make sample project using `react-native init ` command.  

```unix  
   $ react-native init SendBirdSample  
```  

If you ended making React Native sample project, open this folder using atom or other text editor.

![Open folder using Atom](https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/atom_init.png)  


## Installation SendBird JavaScript SDK
This tutorial will use SendBird's `JavaScript SDK`.  
Download the latest SendBird's `JavaScript SDK` file.  

<a class="sendbird-btn sendbird-btn--green" href="https://github.com/smilefam/SendBird-SDK-JavaScript" target="_blank">Latest SendBird JavaScript SDK - Click here to download</a>  

or  

```unix  
   bower install sendbird  
```  

or  
  
```unix  
   npm install sendbird  
```  

The recommended way is npm install.  
  
```unix  
   $ cd SendBirdSample  
   $ npm install sendbird --save  
```  
  
![Install SendBird JavaScript SDK](https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/install_sdk.png)  


### (Optional) Download the Sample App  
This app is a simple chat app that we are going to build through this tutorial.  
<a class="sendbird-btn sendbird-btn--green" href="https://github.com/smilefam/SendBird-JavaScript/tree/master/tutorial-react-native-sample/SendBirdSample" target="_blank">Tutorial Sample app - Click here to see repository</a>  

This app is a sample app that are built with more various features.  
<a class="sendbird-btn sendbird-btn--green" href="https://github.com/smilefam/SendBird-JavaScript/tree/master/basic-react-native-sample/SendBirdReactNativeSample" target="_blank">Basic Sample app - Click here to see repository</a>  
  
  
### Used list
 * [Navigator](http://facebook.github.io/react-native/docs/navigator.html#content)  
 * [View](http://facebook.github.io/react-native/docs/view.html#content)  
 * [Text](http://facebook.github.io/react-native/docs/text.html#content)  
 * [Image](http://facebook.github.io/react-native/docs/image.html#content)  
 * [TextInput](http://facebook.github.io/react-native/docs/textinput.html#content)  
 * [ListView](http://facebook.github.io/react-native/docs/listview.html#content)  
 * [ScrollView](http://facebook.github.io/react-native/docs/scrollview.html#content)  
 * [TouchableHighlight](http://facebook.github.io/react-native/docs/touchablehighlight.html#content)  
 * [StyleSheet](http://facebook.github.io/react-native/docs/stylesheet.html#content)  
 * [Dimensions](http://facebook.github.io/react-native/docs/dimensions.html#content)  
  
  
[Next Step](create_login.md)  
