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

import React, { Component } from 'react';
import {
  AppRegistry,
  StyleSheet,
  Text,
  View,
  ScrollView,
  Button,
  Dimensions,
  Modal,
} from 'react-native'
import { graphql, compose } from 'react-apollo'
import gql from 'graphql-tag'
import { connect } from 'react-redux'
import { bindActionCreators } from 'redux'
import { showProfile, hideProfile } from './actions/profile'
import { styles } from './styles'

var { width, height } = Dimensions.get('window')

class App extends Component {

	constructor(props) {
	  super(props)
	}

	state = {
		modalVisible: false,
	}

	showProfileButtonPress() {
		const { showProfile } = this.props.actions
		const userProfile = {
			id: 110044003300,
			name: 'Pablo Escobar',
			email: 'pablo.e@gmail.com',
			tel: '+770780039944'
		}
		showProfile(userProfile)
	}

	hideProfileButtonPress() {
		const { hideProfile } = this.props.actions
		// dispatch hide profile
		hideProfile()
	}

  render() {

  	const { myProfile } = this.props
  	const visibleProfile = myProfile.visible
  	var data = this.props.data
  	console.log(data)
  	if (data.loading) {
  		return (
  		<View style={styles.container}>
  			<Text>Loadding...</Text>
  		</View>
  		)
  	} else {
	    return (
	      <View style={styles.container}>
		      <View style={styles.header}>
		      	<View style={styles.headerTitle}>
		      		<Button onPress={()=> this.showProfileButtonPress() } title="Show Profile" />
		      	</View>
		      </View>
		      <ScrollView style={{width: width}}>
			      {data.allPeople.edges.map((item)=> 
			        <Text key={item.node.id} style={styles.instructions}>
			          {item.node.name}
			        </Text>	      	
			      )} 
		      </ScrollView>

		      <Modal animationType={"fade"} transparent={true} visible={visibleProfile}>
		      	<View style={{width: width, height: height, backgroundColor: "floralwhite", justifyContent: 'center', alignItems: 'center'}}>
		      		<Text style={{fontWeight: 'bold', fontSize: 20, margin: 10}}>My profile</Text>
		      		<Text>ID: {myProfile.id}</Text>
		      		<Text>Name: {myProfile.name}</Text>
		      		<Text>Email: {myProfile.email}</Text>
		      		<Text>Tel: {myProfile.tel}</Text>
		      		<Button onPress={()=> this.hideProfileButtonPress()} title="Close" />
		      	</View>
		      </Modal>
	      </View>
	    )  		
  	}
  }
}

const playlistQuery = gql`
	query {
	  allPeople {
	    edges {
	      node {
	        id
	        name
	      }
	    }
	  }
	}`

function mapStateToProps(state) {
	return {
		myProfile: state.profile
	}
}

function mapDispatchToProps(dispatch) {
	return {
		actions: bindActionCreators({showProfile, hideProfile}, dispatch)
	}
} 

export default compose(
	graphql(playlistQuery),
	connect(mapStateToProps, mapDispatchToProps)
)(App)
