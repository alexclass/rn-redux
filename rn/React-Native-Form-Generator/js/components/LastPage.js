import React, { Component } from 'react'
import {
  StyleSheet,
  Text,
  View
} from 'react-native'
import { Container, Content, Button, Header, Title, H1 } from 'native-base'
import { Grid, Col, Row } from 'react-native-easy-grid'
import { Actions, ActionConst } from 'react-native-router-flux'

export default class LastPage extends Component {
  render(){
    return (
      <View style={{flex: 1}}>
        <Header>
          <Title>No more to continue...</Title>
        </Header>        
        <Grid>
          <Row size={8}>
            <Content>
             <View style={{top: 200, alignItems:"center"}}><H1>nothing formed from here.</H1></View>
            </Content>
          </Row>
          <Row size={1}>
            <Col style={{justifyContent: 'flex-end', alignItems: 'flex-end'}}>
                <Button block danger onPress={()=> Actions.welcome({ type: ActionConst.RESET })}>Play Again.</Button>
            </Col>
          </Row>
        </Grid>          
      </View>      
    )
  }
}