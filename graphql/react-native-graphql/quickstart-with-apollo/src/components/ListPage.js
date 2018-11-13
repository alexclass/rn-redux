import React from 'react'
import Post from './Post'
import { graphql, gql } from 'react-apollo'
import {
  View,
  TouchableHighlight,
  ListView,
  Modal,
  StyleSheet,
  Text
} from 'react-native'
import CreatePage from './CreatePage'

const getKey = gql`
  query {
    key(id: 2, accesskey: "AAAA", pin: "P1P1P1") {
      id
      key
    }
  }`

class ListPage extends React.Component {

  constructor(props) {
    super(props)
    console.log('1.listpage props : ', props)
    const ds = new ListView.DataSource({rowHasChanged: (r1, r2) => r1 !== r2})
    this.state = {
      dataSource: ds.cloneWithRows([]),
      modalVisible: false,
      user: undefined,
    }

  }

  componentWillReceiveProps(nextProps) {
    console.log('1.listpage componentWillReceiveProps : ', nextProps)
    if (!nextProps.getKey.loading && !nextProps.getKey.error) {
      const {dataSource} = this.state
      console.log('2.listpage componentWillReceiveProps datasource : ', dataSource)
      this.setState({
        dataSource: dataSource.cloneWithRows(nextProps.getKey.allPosts),
      })
    }
  }

  render () {
    if (this.props.getKey.loading) {
      return (<Text>Loading</Text>)
    }

    return (
      <View style={styles.container}>

        <Modal
          animationType='slide'
          transparent={true}
          visible={this.state.modalVisible}
        >
          <CreatePage
            onComplete={() => {
              this.props.getKey.refetch()
              this.setState({modalVisible: false})
          }}/>
        </Modal>

        <ListView
          enableEmptySections={true}
          dataSource={this.state.dataSource}
          renderRow={(post) => (
            <Post
              description={post.description}
              imageUrl={post.imageUrl}
            />
          )}
        />
        <TouchableHighlight
          style={styles.createPostButtonContainer}
          onPress={this._createPost}
        >
          <Text style={styles.createPostButton}>Create Post</Text>
        </TouchableHighlight>
      </View>
    )
  }

  _createPost = () => {
    console.log('1.listpage _createPost')
    // this.props.router.push('/create');
    this.setState({modalVisible: true})

  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    paddingTop: 22
  },
  createPostButtonContainer: {
    justifyContent: 'center',
    alignItems: 'center',
  },
  createPostButton: {
    backgroundColor: 'rgba(39,174,96,1)',
    color: 'white',
    textAlign: 'center',
    fontSize: 22,
    height: 60,
    width: 480,
    paddingTop: 18,
  }
})

const ListPageWithData = graphql(getKey, {name: 'getKey'})(ListPage)
export default ListPageWithData
