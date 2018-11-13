/**
 * BY THUNDERBIRD7
 * FoolStack Developer
 */

import React, { Component, PropTypes } from 'react'
import {
  StyleSheet,
  Text,
  View,
  Modal, 
  TouchableHighlight,
  TouchableOpacity,
  RefreshControl,
  Platform,  
} from 'react-native'
import { 
  Container, 
  Content, 
  Header, 
  Title, 
  List, 
  ListItem,
  Thumbnail,
  H3,
  H1,
  Spinner,
} from 'native-base'
import ModalView from './ModalView'
import { graphql } from 'react-apollo'
import gql from 'graphql-tag'
import codePush from 'react-native-code-push'

const codePushOptions = { 
  checkFrequency: codePush.CheckFrequency.ON_APP_RESUME,
  updateDialog: true,
  installMode: codePush.InstallMode.IMMEDIATE
 }
class App extends Component {

  state = {
    modalVisible: false,
    title: '',
    detail: '',
  }

  constructor(props) {
    super(props)
  }

  setModalVisible(visible) {
    this.setState({modalVisible: visible});
  }

  renderRow(item) {
    return (
        <ListItem onPress={()=> {
            this.setModalVisible(true)
            this.setState({title: item.node.title, detail: item.node.openingCrawl})
        }}>
            <Thumbnail circular size={80} style={{backgroundColor: 'gray'}} />
            <H3>{item.node.title}</H3>
            <Text note>By {item.node.director}</Text>
            <Text note>Release {item.node.releaseDate}</Text>
        </ListItem>
    )
  }

  render() {
    // get allfilms props from graphql
    const data = this.props.data
    console.log(data)

    if (data.loading) {
      return (<Spinner />)
    } else {
      return (
        <Container>
          <Header><Title>Favorite Movie</Title></Header>
          <Content>
            <List 
              dataArray={data.allFilms.edges} 
              renderRow={this.renderRow.bind(this)} />
            <ModalView 
              title={this.state.title}
              detail={this.state.detail}
              visible={this.state.modalVisible} 
              onDismiss={()=> this.setModalVisible(false)}/>              
          </Content>        
        </Container>)
      } 
  }

}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#F5FCFF',
  },
  welcome: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  },
  instructions: {
    textAlign: 'center',
    color: '#333333',
    marginBottom: 5,
  },
});

const gqlQuery = gql`
  query {
    allFilms {
      edges {
        node {
          id
          title
          openingCrawl
          director
          releaseDate
        }
      }
    }
  }
`

// wrap gql and codepush to container.
const AppWithData = graphql(gqlQuery)
App = codePush(codePushOptions)(App)

export default AppWithData(App)
