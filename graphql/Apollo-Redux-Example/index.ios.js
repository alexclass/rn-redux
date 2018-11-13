/**
 * Example for Integration Apollo Client and Redux
 * https://github.com/Thunderbird7/React-Native-GraphQL-Apollo-Client
 *
 * Yuttana K.
 * Mobile Engineer
 * Jitta.com
 *
 * @flow
 */
 
import React, { Component } from 'react'
import { AppRegistry, } from 'react-native'
import { ApolloProvider } from 'react-apollo'
import { client } from './client'
import { configureStore } from './configureStore'
import App from './App'

export default class ApolloRedux extends Component {

  render() {
    return (
      <ApolloProvider store={configureStore} client={client}>
        <App />
      </ApolloProvider>
    )
  }
}

AppRegistry.registerComponent('ApolloRedux', () => ApolloRedux)
