import React, { Component } from 'react'
import {
  AppRegistry,
  StyleSheet,
  Text,
  View
} from 'react-native'
import { Container, Content, Button, Icon, InputGroup, Input, Header, Title, List, ListItem, H1 } from 'native-base'
import { Grid, Col, Row } from 'react-native-easy-grid'
import { Actions } from 'react-native-router-flux'
import LastPage from './LastPage'
import formGenerator from '../formGenerator'
import json from '../forms.json'

export default class ApplicationForm extends Component {

  constructor(props) {
    super(props)
  }

  state = {
    pageIndex: this.props.page || 1
  }

  render() {
    let jsonForm = json[`page${this.state.pageIndex}`]
    if (jsonForm === undefined) {
      // Next page after form is nothing
      return (<LastPage />)
    }

    let fields = formGenerator(jsonForm.fields)
    return (
      <View style={styles.container}>
        <Header>
          <Button onPress={() => Actions.pop()} transparent>
            <Icon name="ios-arrow-back" />
          </Button>
          <Title>{jsonForm.title}</Title>
        </Header>
        <Grid>
          <Row size={8}>
            <Content style={{}}>
              <View style={{ paddingLeft: 20, paddingRight: 20 }}>
                {fields}
              </View>
            </Content>
          </Row>
          <Row size={1}>
            <Col style={{ justifyContent: 'flex-end', alignItems: 'flex-end' }}>
              <Button block info onPress={() => Actions.applicationForm({ page: this.state.pageIndex + 1, })}>Next</Button>

            </Col>
          </Row>
        </Grid>
      </View>
    )
  }

}

const styles = StyleSheet.create({
  container: {
    flex: 1,
  }
})