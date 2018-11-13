Create Channel List View
=================================
In this part, we are going to bring `Channel List` and print them on our screen.  


### 1. Make Channel List file
First, make a `channels.js` file under `components` directory.  
Modify `src/components/channels.js` file as follows.  
  
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
          <Text style={{color: '#fff'}}>Channels</Text>
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
  
Add `channels` we made in `ROUTES` of `src/main.js` file.   
  
```javascript  
  ...
  var Login = require('./components/login');
  var Channels = require('./components/channels');
  
  var ROUTES = {
    login: Login,
    channels: Channels
  };
  ...
```  
  

Modify `onPress` function at `src/components/login.js` file as follows   

  
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
        this.props.navigator.push({ name: 'channels' });
      },
      errorFunc: (status, error) => {
        this.setState({username: ''});
      }
    });
  }
  ...
```  
  

Refresh the `Simulator` (command + R) and insert `nickname`. Then click `LOGIN` button.    
Following screen will be displayed if everything is succeeded.    
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/channels-01.png" width=372 height=665 />    
  
  
### 2. Get Channel List
Let's load `Channel List` and print with SendBird `JavaScript SDK`.  
In this part, we are going to use [Image](http://facebook.github.io/react-native/docs/image.html#content) and [ListView](http://facebook.github.io/react-native/docs/listview.html#content).  
Modify `src/components/channels.js` file as follows.  
  
```javascript  
  
  var React = require('react-native');
  var {
    View,
    Text,
    Image,
    TextInput,
    ListView,
    TouchableHighlight,
    StyleSheet
  } = React;
  
  var sendbird = require('sendbird');
  var PULLDOWN_DISTANCE = 40;
  
  module.exports = React.createClass({
    getInitialState: function() {
      var ds = new ListView.DataSource({rowHasChanged: (r1, r2) => r1 !== r2});
      return {
        channelList: [],
        dataSource: ds.cloneWithRows([]),
        page: 0,
        next: 0,
        channelName: ''
      };
    },
    componentWillMount: function() {
      this.getChannelList(1);
    },
    render: function() {
      return (
        <View style={styles.container}>
          <View style={styles.listContainer}>
            <ListView
              dataSource={this.state.dataSource}
              renderRow={(rowData) =>
                <TouchableHighlight onPress={() => this.onChannelPress(rowData.channel_url)}>
                  <View style={styles.listItem}>
                    <View style={styles.listIcon}>
                      <Image style={styles.channelIcon} source={{uri: rowData.cover_img_url}} />
                    </View>
                    <View style={styles.listInfo}>
                      <Text style={styles.titleLabel}># {rowData.name}</Text>
                      <Text style={styles.memberLabel}>{rowData.member_count} members</Text>
                    </View>
                  </View>
                </TouchableHighlight>
              }
              onEndReached={() => this.getChannelList(this.state.next)}
              onEndReachedThreshold={PULLDOWN_DISTANCE}
            />
          </View>
        </View>
      );
    },
    onChannelPress: function(url) {
      console.log(url);
    },
    getChannelList: function(page) {
      if (page == 0) {
        return;
      }
      sendbird.getChannelList({
        page: page,
        limit: 20,
        successFunc : (data) => {
          this.setState({channelList: this.state.channelList.concat(data.channels)}, () => {
            this.setState({
              dataSource: this.state.dataSource.cloneWithRows(this.state.channelList),
              page: data.page,
              next: data.next
            });
          });
        },
        errorFunc: (status, error) => {
          console.log(status, error);
        }
      });
    }
  });
  
  var styles = StyleSheet.create({
    container: {
      flex: 1,
      justifyContent: 'center',
      alignItems: 'stretch',
      backgroundColor: '#ffffff'
    },
    listContainer: {
      flex: 11,
      justifyContent: 'center',
      alignItems: 'stretch',
      marginTop: 10
    },
    listItem: {
      flex: 1,
      flexDirection: 'row',
      justifyContent: 'center',
      alignItems: 'center',
      backgroundColor: '#f7f8fc',
      borderBottomWidth: 0.5,
      borderColor: '#D0DBE4',
      padding: 5
    },
    listIcon: {
      justifyContent: 'flex-start',
      paddingLeft: 10,
      paddingRight: 15
    },
    channelIcon: {
      width: 30,
      height: 30
    },
    listInfo: {
      flex: 1,
      justifyContent: 'flex-start'
    },
    titleLabel: {
      fontSize: 15,
      fontWeight: '600',
      color: '#60768b',
    },
    memberLabel: {
      fontSize: 13,
      fontWeight: '400',
      color: '#abb8c4',
    }
  });

```  
  
Following screen means that the process succeeded.   
If you scroll down and move to lowest position, `getChannelList` function that you registered at `onEndReached` is called.  
And then you can check this function brings next list.  
When you click one of the channel list, you can check `onChannelPress` is called with `Chrome Developer Tools`.  
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/channels-02.png" width=933 height=722 />    
  

### 3. Join Channel
Modify `onChannelPress` function as follows that is called when you click channel.  
  
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
                console.log(channel);
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

Following screen shows when `Game Insight` is selected from `Channel List`.  
Following screen means that the process succeeded.   
  
<img src="https://s3-ap-northeast-1.amazonaws.com/sendbird-react-native-tutorial-image/channels-03.png" width=913 height=708 />  
  
  
At the next part, we are going to make sending and receiving message function. [Next Step](create_chat_view.md)  
  
