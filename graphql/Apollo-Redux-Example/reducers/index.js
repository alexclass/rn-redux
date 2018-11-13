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
 
import { combineReducers, } from 'redux'
import { client } from '../client'
import { profileReducer } from './profile'

export const rootReducer = combineReducers({
  profile: profileReducer,
  apollo: client.reducer()
})