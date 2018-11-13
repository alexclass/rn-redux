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
 
import ApolloClient, { createNetworkInterface } from 'apollo-client'

export const client = new ApolloClient({ 
  networkInterface: createNetworkInterface({ uri: 'http://graphql-swapi.parseapp.com' }), 
})