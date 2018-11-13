Create Login View
=================================
In this part, we are going to make a nickname input section and entrance button.  


### 1. Run React Native
First, run the project that we created previous step.  
  
```unix  
   $ npm start  
   $ react-native run-ios  
```  
  
On the other way, you can open this project by xcode and execute.  
Following screen will be displayed.  
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/run-ios-01.png" width=510 height=420 />    
  
  
### 2. Make Navigator
In this part, we are going to add screen transition in our app with [Navigator](http://facebook.github.io/react-native/docs/navigator.html#content).   
First, make a `src` directory under the `root` directory and make a `main.js` file inside of the `src` directory.  
Second, make a `components` directory under the `src` directory and make a `login.js` file inside of the `components` directory.  
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/make-file-01.png" width=202 height=329 />  
  
Modify `index.ios.js` file as follows.  
  
```javascript  

  var React = require('react-native');
  var {
    AppRegistry
  } = React;
  
  var Main = require('./src/main')
  
  AppRegistry.registerComponent('SendBirdSample', () => Main);
  
```  
  
  
Modify `src/main.js` file as follows.  
  
```javascript  

  var React = require('react-native')
  var {
    Navigator,
    StyleSheet
  } = React;
  
  var Login = require('./components/login');
  
  var ROUTES = {
    login: Login
  };
  
  module.exports = React.createClass({
    renderScene: function(route, navigator) {
      var Component = ROUTES[route.name];
      return <Component route={route} navigator={navigator} />;
    },
    render: function() {
      return (
        <Navigator
          style={ styles.container }
          initialRoute={ {name: 'login'} }
          renderScene={this.renderScene}
          configureScene={ () => { return Navigator.SceneConfigs.FloatFromRight; } }
        />
      );
    }
  });
  
  var styles = StyleSheet.create({
    container: {
      flex: 1
    }
  });

  
```  
  
  
Modify `src/components/login.js` file as follows.  
  
```javascript  

  var React = require('react-native');
  var {
    View,
    Text,
    StyleSheet
  } = React;
  
  module.exports = React.createClass({
    render: function() {
      return (
        <View style={styles.container}>
          <Text style={{color: 'white'}}>SendBird JavaScript SDK!!!</Text>
        </View>
      );
    }
  });
  
  var styles = StyleSheet.create({
    container: {
      flex: 1,
      justifyContent: 'center',
      alignItems: 'stretch',
      backgroundColor: '#6E5BAA'
    }
  });

  
```  
  

Refresh the Simulator.  
Following screen will be displayed.  
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/login-image-01.png" width=372 height=684 />  
  

### 3. Make Login View
We make one input box and one login button.  
We need [TextInput](http://facebook.github.io/react-native/docs/textinput.html#content), [TouchableHighlight](http://facebook.github.io/react-native/docs/touchablehighlight.html#content) and `getInitialState` for this view.  
`getInitialState` is initial code before call `render` function.  
And for SendBird login, need `sendbird` that we install package previous step.  

Add `TextInput`, `TouchableHighlight` and `getInitialState` function.  
  
```javascript  
  
  var React = require('react-native');
  var {
    View,
    Text,
    TextInput,
    TouchableHighlight,
    StyleSheet
  } = React;
  
  module.exports = React.createClass({
    getInitialState: function() {
      return {
        username: ''
      };
    },
    render: function() {
      return (
        <View style={styles.container}>
          <View style={styles.loginContainer}>
            <TextInput
              style={styles.input}
              value={this.state.username}
              onChangeText={(text) => this.setState({username: text})}
              placeholder={'Enter User Nickname'}
              maxLength={12}
              multiline={false}
              />
  
            <TouchableHighlight
              style={styles.button}
              underlayColor={'#328FE6'}
              onPress={this.onPress}
              >
              <Text style={styles.label}>LOGIN</Text>
            </TouchableHighlight>
          </View>
        </View>
      );
    },
    onPress: function() {
      console.log(this.state.username);
    }
  });
  
  var styles = StyleSheet.create({
    container: {
      flex: 1,
      justifyContent: 'center',
      alignItems: 'stretch',
      backgroundColor: '#6E5BAA'
    },
    loginContainer: {
      flex: 1,
      justifyContent: 'center',
      alignItems: 'center',
    },
    input: {
      width: 250,
      color: '#555555',
      padding: 10,
      height: 50,
      borderColor: '#32C5E6',
      borderWidth: 1,
      borderRadius: 4,
      alignSelf: 'center',
      backgroundColor: '#ffffff'
    },
    button: {
      justifyContent: 'center',
      alignItems: 'center',
      borderWidth: 1,
      borderRadius: 5,
      borderColor: '#328FE6',
      padding: 10,
      marginTop: 10,
      backgroundColor: '#32c5e6'
    },
    label: {
      width: 230,
      flex: 1,
      alignSelf: 'center',
      textAlign: 'center',
      fontSize: 20,
      fontWeight: '600',
      color: '#ffffff'
    }
  });

```  
  
Refresh the Simulator.  
Following screen will be displayed.  
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/login-image-02.png" width=372 height=684 />  
  

### 3. Debug with Chrome developer tools
Let's check how to use `console.log()` for validation when you develop.  
Press `command + D` and you can see `Debug in Chrome` button as follows.  
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/login-image-03.png" width=373 height=685 />    
  
When you click this button, `Chrome` window will come out and You can check the value on `Console` tab in Chrome developer tool.  
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/login-image-04.png" width=766 height=221 />  
    
In this code, `onPress` function is called when you click `LOGIN` button.  
When you insert `nickname` in `TextInput` and click `LOGIN` button if the insert value is displayed on `Chrome Developer Tools`, than you can think the process succeeded.  
The following is the success state.  
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/login-image-05.png" width=893 height=481 />  
  

### 4. Login SendBird
Declare this to use SendBird `JavaScript SDK`.  
  
```javascript  
  
  var React = require('react-native');
  var {
    View,
    Text,
    TextInput,
    TouchableHighlight,
    StyleSheet
  } = React;
  
  var sendbird = require('sendbird');
  
  module.exports = React.createClass({
    getInitialState: function() {
      return {
        username: ''
      };
    },
  ...
```  
  
Modify `onPress` function as follows that is called when you clicked `LOGIN` button.
`app_id` refers to `app_id` of Sample Application that is used in SendBird.  
You can insert your own `app_id` of SendBird.  
  
<a class="sendbird-btn sendbird-btn--green" href="https://dashboard.sendbird.com/" target="_blank">Make SendBird Application</a>  
    
  
```javascript  
  ...
  onPress: function() {
    sendbird.init({
      app_id: 'A7A2672C-AD11-11E4-8DAA-0A18B21C2D82',
      guest_id: this.state.username,
      user_name: this.state.username,
      image_url: "",
      access_token: "",
      successFunc: (data) => {
        console.log('success');
      },
      errorFunc: (status, error) => {
        this.setState({username: ''});
      }
    });
  }
  ...
```  
  
When you insert `nickname` and click `LOGIN` button if following screen is displayed, than you can think the process succeeded.  

  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/login-image-06.png" width=901 height=352 />  
  

At the next part, we are going to bring `Channel List` and print to our screen. [Next Step](create_channel_list.md)  
  
  