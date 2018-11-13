Create Chat View
=================================
In this part, we are going to implement a simple text message feature.    


### 1. Make Chat file
First, make a `chat.js` file under `components` directory.  
Modify `src/components/chat.js` file as follows.  
  
```javascript  
    
  var React = require('react-native');
  var {
    View,
    Text,
    StyleSheet
  } = React;
  
  var sendbird = require('sendbird');
  
  module.exports = React.createClass({
    render: function() {
      return (
        <View style={styles.container}>
          <Text style={{color: '#fff'}}>Chat</Text>
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
  
Add `chat` we made in `ROUTES` of `src/main.js` file.   
  
```javascript  
  ...
  var Login = require('./components/login');
  var Channels = require('./components/channels');
  var Chat = require('./components/chat');
  
  var ROUTES = {
    login: Login,
    channels: Channels,
    chat: Chat
  };
  ...
```  
  

Modify `onChannelPress` function at `src/components/channels.js` file as follows   
  
```javascript  
  ...
  onChannelPress: function(url) {
    sendbird.joinChannel(
      url,
      {
        successFunc: (data) => {
          sendbird.connect({
            successFunc: (data) => {
              sendbird.getChannelInfo((channel) => {
                this.props.navigator.push({ name: 'chat' });
              });
            },
            errorFunc: (status, error) => {
              console.log(status, error);
            }
          });
        },
        errorFunc: (status, error) => {
          console.log(status, error);
        }
      }
    );
  }
  ...
```  
  

Refresh the `Simulator` (command + R) and select `channel`.    
Following screen will be displayed if everything is succeeded.    
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/chat-01.png" width=378 height=687 />    
  
  
### 2. Make Button
  
#### 2-1. BackButton
Let's make a `Back` button on top of screen for going back to `Channel List`  
  
```javascript
  
  ...
  module.exports = React.createClass({
    render: function() {
      return (
        <View style={styles.container}>
          <View style={styles.topContainer}>
            <TouchableHighlight
              underlayColor={'#4e4273'}
              onPress={this.onBackPress}
              style={{marginLeft: 15}}
              >
              <Text style={{color: '#fff'}}>&lt; Back</Text>
            </TouchableHighlight>
          </View>
          <View style={styles.chatContainer}>
            <Text style={{color: '#000'}}>Chat</Text>
          </View>
          <View style={styles.inputContainer}>
            <Text style={{color: '#000'}}>Input</Text>
          </View>
        </View>
      );
    },
    onBackPress: function() {
      this.props.navigator.pop();
    }
  });
  
  var styles = StyleSheet.create({
    container: {
      flex: 1,
      justifyContent: 'center',
      alignItems: 'stretch',
      backgroundColor: '#ffffff'
    },
    topContainer: {
      flex: 1,
      flexDirection: 'row',
      justifyContent: 'flex-start',
      alignItems: 'center',
      backgroundColor: '#6E5BAA',
      paddingTop: 20,
    },
    chatContainer: {
      flex: 11,
      justifyContent: 'center',
      alignItems: 'stretch'
    },
    inputContainer: {
      flex: 1,
      justifyContent: 'center',
      alignItems: 'stretch'
    }
  });
  
```
  
Following screen will be displayed.  
When you click `< Back` you can get back to previous page.  
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/chat-02.png" width=377 height=691 />    
  

#### 2-2. SendButton
Let's make TextInput and `Send` button for sending messages.  

  
```javascript  
  
  var React = require('react-native');
  var {
    View,
    Text,
    TouchableHighlight,
    TextInput,
    Dimensions,
    StyleSheet
  } = React;
  
  var sendbird = require('sendbird');
  var windowSize = Dimensions.get('window');
  
  module.exports = React.createClass({
    getInitialState: function() {
      return {
        message: ''
      };
    },
    render: function() {
      return (
        <View style={styles.container}>
          <View style={styles.topContainer}>
            <TouchableHighlight
              underlayColor={'#4e4273'}
              onPress={this.onBackPress}
              style={{marginLeft: 15}}
              >
              <Text style={{color: '#fff'}}>&lt; Back</Text>
            </TouchableHighlight>
          </View>
          <View style={styles.chatContainer}>
            <Text style={{color: '#000'}}>Chat</Text>
          </View>
          <View style={styles.inputContainer}>
            <View style={styles.textContainer}>
              <TextInput
                style={styles.input}
                value={this.state.message}
                onChangeText={(text) => this.setState({message: text})}
                />
            </View>
            <View style={styles.sendContainer}>
              <TouchableHighlight
                underlayColor={'#4e4273'}
                onPress={() => this.onSendPress()}
                >
                <Text style={styles.sendLabel}>SEND</Text>
              </TouchableHighlight>
            </View>
          </View>
        </View>
      );
    },
    onBackPress: function() {
      this.props.navigator.pop();
    },
    onSendPress: function() {
      console.log(this.state.message);
      this.setState({message: ''});
    }
  });
  
  var styles = StyleSheet.create({
    container: {
      flex: 1,
      justifyContent: 'center',
      alignItems: 'stretch',
      backgroundColor: '#ffffff'
    },
    topContainer: {
      flex: 1,
      flexDirection: 'row',
      justifyContent: 'flex-start',
      alignItems: 'center',
      backgroundColor: '#6E5BAA',
      paddingTop: 20,
    },
    chatContainer: {
      flex: 11,
      justifyContent: 'center',
      alignItems: 'stretch'
    },
    inputContainer: {
      flex: 1,
      flexDirection: 'row',
      justifyContent: 'space-around',
      alignItems: 'center',
      backgroundColor: '#6E5BAA'
    },
    textContainer: {
      flex: 1,
      justifyContent: 'center'
    },
    sendContainer: {
      justifyContent: 'flex-end',
      paddingRight: 10
    },
    sendLabel: {
      color: '#ffffff',
      fontSize: 15
    },
    input: {
      width: windowSize.width - 70,
      color: '#555555',
      paddingRight: 10,
      paddingLeft: 10,
      paddingTop: 5,
      height: 32,
      borderColor: '#6E5BAA',
      borderWidth: 1,
      borderRadius: 2,
      alignSelf: 'center',
      backgroundColor: '#ffffff'
    },
  });
  
```  
  
Following screen will be displayed.  
When you click `SEND` you can check the inserted value on `Chrome Developer Tools`.  
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/chat-03.png" width=938 height=711 />    
  

### 3. Chat Message
Let's make a feature that bring existing messages, send them and receive them.  
Modify `getInitialState` as follows.  
  
```javascript  
  ...
  getInitialState: function() {
    return {
      message: '',
      messageList: []
    };
  },
  ...
```  
  
Add `componentWillMount` as follows.  
`componentWillMount` is called before the initial rendering occurs.  
  
```javascript
  ...
  componentWillMount: function() {
    sendbird.events.onMessageReceived = (obj) => {
      this.setState({messageList: this.state.messageList.concat([obj])});
    };
    this.getMessages();
  },
  ...
```  
  
Make `getMessages` as follows.  
  
```javascript  
  ...
  getMessages: function() {
    sendbird.getMessageLoadMore({
      limit: 100,
      successFunc: (data) => {
        var _messageList = [];
        data.messages.reverse().forEach(function(msg, index){
          if(sendbird.isMessage(msg.cmd)) {
            _messageList.push(msg.payload);
          }
        });
        this.setState({ messageList: _messageList.concat(this.state.messageList) });
      },
      errorFunc: (status, error) => {
        console.log(status, error);
      }
    });
  }
  ...
```  
  
Modify `onSendPress` as follows.  
  
```javascript  
  ...
  onSendPress: function() {
    sendbird.message(this.state.message);
    this.setState({message: ''});
  },
  ...
```
  
Modify `render` as follows.  
  
```javascript  
  ...
  render: function() {
    var list = this.state.messageList.map((item, index) => {
      return (
        <View
          style={styles.messageContainer}
          key={index}
          >
          <Text style={this.nameLabel}>
            {item.user.name}
            <Text style={styles.messageLabel}> : {item.message}</Text>
          </Text>
        </View>
      );
    });

    return (
      <View style={styles.container}>
        <View style={styles.topContainer}>
          <TouchableHighlight
            underlayColor={'#4e4273'}
            onPress={this.onBackPress}
            style={{marginLeft: 15}}
            >
            <Text style={{color: '#fff'}}>&lt; Back</Text>
          </TouchableHighlight>
        </View>
        <View style={styles.chatContainer}>
          <ScrollView
            ref={(c) => this._scrollView = c}
            onScroll={this.handleScroll}
            scrollEventThrottle={16}
            onContentSizeChange={(e) => {}}
          >
          {list}
          </ScrollView>
        </View>
        <View style={styles.inputContainer}>
          <View style={styles.textContainer}>
            <TextInput
              style={styles.input}
              value={this.state.message}
              onChangeText={(text) => this.setState({message: text})}
              />
          </View>
          <View style={styles.sendContainer}>
            <TouchableHighlight
              underlayColor={'#4e4273'}
              onPress={() => this.onSendPress()}
              >
              <Text style={styles.sendLabel}>SEND</Text>
            </TouchableHighlight>
          </View>
        </View>
      </View>
    );
  },
  ...
``` 
  
Modify `onBackPress` as follows.  

```javascript  
  ...
  onBackPress: function() {
    sendbird.disconnect();
    this.props.navigator.pop();
  },
  ...
```
  
Modify `onChannelPress` function at `src/components/channels.js` file as follows  
  
```javascript  
  ...
  onChannelPress: function(url) {
    sendbird.joinChannel(
      url,
      {
        successFunc: (data) => {
          sendbird.connect({
            successFunc: (data) => {
              sendbird.getChannelInfo((channel) => {
                sendbird.connect({
                  successFunc: (data) => { this.props.navigator.push({ name: 'chat' }); },
                  errorFunc: (status, error) => { console.log(status, error); }
                });
              });
            },
            errorFunc: (status, error) => {
              console.log(status, error);
            }
          });
        },
        errorFunc: (status, error) => {
          console.log(status, error);
        }
      }
    );
  },
  ...
```
  
Because it has the same `app_id` as [sample.sendbird.com](https://sample.sendbird.com/) has, you can check that messages are transmitted successfully in there.  
Refresh and test your application. Following screen will be displayed.  
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/chat-04.png" width=911 height=766 />    
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/chat-05.png" width=849 height=759 />    
  
You can check the messages are transmitted successfully.  
You can get another sample with more features below.  

<a class="sendbird-btn sendbird-btn--green" href="https://github.com/smilefam/SendBird-JavaScript/tree/master/basic-sample" target="_blank">Basic Sample app - Click here to see repository</a>  



