# SendBird JavaScript Widget Sample
This is a sample chat widget built using using the [SendBird SDK](https://github.com/smilefam/SendBird-SDK-JavaScript). It can be used to add a functional chat widget to any website.  


## [Demo](https://sample.sendbird.com/widget/)

You can try out a live demo from the link [here](https://sample.sendbird.com/widget/). Click on the button at the bottom-right corner of the webpage to try out the widget. Choose any 'User ID' and 'Nickname' to log in and participate in chats.


## Setup
1. The `body` must have a `div` element whose id is `sb_widget`.
  
```html
<body>
  <div id="sb_widget"></div>
</body>
```

2. Import the [`SendBird SDK`](https://github.com/smilefam/SendBird-SDK-JavaScript).  
3. Import the `widget.SendBird.js` file.
```javascript
<script src="SendBird.min.js"></script>
<script src="build/widget.SendBird.js"></script>
```


## Customizing the widget
If you refresh your browser window, you need to reconnect to SendBird. To retain connection on browser refresh, you must implement an appropriate `event handler`. 

If you wish to issue an `access_token` for your user, modify the `connect function` in `src/sendbird.js`.  

1. Install npm

        npm install --save-dev

2. Modify files.
3. Create a bundle file.

        webpack -p


## File Structure
```
    |-- build
        |-- widget.SendBird.js              - SendBird Widget Bundle file
    |-- node_modules
        |-- ...                             - (node packages)
    |-- src
        |-- js
            |-- elements  
                |-- elements.js             - elements root class
                |-- spinner.js              - spinner element
                |-- widget-btn.js           - widget button element
                |-- popup.js                - popup element
                |-- list-board.js           - channel list element
                |-- chat-section.js         - chat element
            |-- consts.js                   - const variables
            |-- utils.js                    - util functions
            |-- sendbird.js                 - sendbird functions
            |-- widget.js                   - widget functions
        |-- scss
            |-- mixins 
                |-- _border-radius.scss     - border radius mixin  
                |-- _box-shadow.scss        - box shadow mixin
                |-- _state.scss             - element state mixin
                |-- _transform.scss         - transform mixin
            |-- _mixins.scss                - import mixin
            |-- _variables.scss             - css variables
            |-- _animation.scss             - animation
            |-- _icons.scss                 - icon 
            |-- widget.scss                 - main css  
|-- .eslintrc.js                            - lint setting 
|-- webpack.config.js                       - widget setting 
|-- package.json                            - npm package 
|-- SendBird.min.js                         - SendBird SDK 
|-- index.html                              - sample file
|-- README.md
```
