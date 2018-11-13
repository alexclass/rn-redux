import React, { Component } from 'react'
import {Actions, Scene, Router} from 'react-native-router-flux'
import Welcome from './js/components/Welcome'
import ApplicationForm from './js/components/ApplicationForm'

const scenes = Actions.create(
  <Scene key="root" hideNavBar>
    <Scene key="welcome" component={Welcome} title="Welcome" intial />
    <Scene key="applicationForm" component={ApplicationForm} />
  </Scene>
)

export default class App extends Component {
  render() {
    return <Router scenes={scenes} />
  }
}