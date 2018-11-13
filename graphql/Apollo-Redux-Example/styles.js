import { StyleSheet, Dimensions } from 'react-native'
var { width, height } = Dimensions.get('window')

export const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#F5FCFF',
    marginTop: 22,
  },
  header: {
  	backgroundColor: 'floralwhite',
  	width: width,
  	height: 44,
  	borderBottomWidth: 1,
  	borderBottomColor: 'lightgray'
  },
  headerTitle: {
  	height: 44,
  	justifyContent: 'center',
  	alignItems: 'center',
  },
  instructions: {
    textAlign: 'center',
    color: '#333333',
    marginBottom: 5,
  },
})