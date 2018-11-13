import React from 'react'
import { ApolloProvider, createNetworkInterface, ApolloClient } from 'react-apollo'
import ListPage from './components/ListPage'

// __SIMPLE_API_ENDPOINT_ looks similar to: `https://api.graph.cool/simple/v1/<PROJECT_ID>`
const __SIMPLE_API_ENDPOINT__ = 'https://keys.usertoken.com/api/graphql'
const networkInterface = createNetworkInterface({ uri: '__SIMPLE_API_ENDPOINT__' })
const client = new ApolloClient({ networkInterface, opts: {mode: "no-cors"} })

export default (
  <ApolloProvider client={client}>
    <ListPage />
  </ApolloProvider>
)
