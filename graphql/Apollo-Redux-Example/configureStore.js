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
 
import { createStore, applyMiddleware, compose, combineReducers } from 'redux'
import { persistStore, autoRehydrate } from 'redux-persist'
import { AsyncStorage } from 'react-native' 
import thunk from 'redux-thunk'
import createLogger from 'redux-logger'
import { client } from './client'
import { rootReducer } from './reducers'

const isDebuggingInChrome = __DEV__ && !!window.navigator.userAgent
const logger = createLogger({
  predicate: (getState, action) => isDebuggingInChrome,
  collapsed: true,
  duration: true,
})

export const configureStore = createStore(
  rootReducer,
  {}, //initial state
  compose(
    applyMiddleware(thunk, logger, client.middleware()),
    autoRehydrate(),
  )
)
//Enable Persistence
persistStore(configureStore, {storage: AsyncStorage})
if (isDebuggingInChrome) {
  window.store = configureStore
}