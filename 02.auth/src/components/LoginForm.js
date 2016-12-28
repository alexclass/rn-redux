import React, { Component } from 'react';
import { Text } from 'react-native';
import firebase from 'firebase';

import { Button, Card, CardSection, Input, Spinner } from './common';

class LoginForm extends Component {
    state = { email: '', password: '', loginError: '', loading: false };
    onButtonPress(){
        const { email, password } = this.state;
        this.setState({ loginError: '', loading: true });
        firebase.auth().signInWithEmailAndPassword(email, password)
            .then(this.onLoginSuccess.bind(this))
            .catch( () => {
                firebase.auth().createUserWithEmailAndPassword(email, password)
                    .then(this.onLoginSuccess.bind(this))
                    .catch(this.onLoginError.bind(this))
            });
    }

    onLoginError(){
        this.setState({ 
            loginError: 'Invalid email or password',
            loading: false
        });
    }
    onLoginSuccess() {
        this.setState({
            email: '',
            password: '',
            loading: false,
            loginError: ''
        });
    }

    renderButton() {
        if (this.state.loading) {
            return <Spinner size="small" />;
        } else {
            return (
                <Button onPress={this.onButtonPress.bind(this)} >
                    LOGIN
                </Button>
            );
        }
    }

    render() {
        console.log('1.LoginForm state: ', this.state)
        return (
            <Card>
                <CardSection>
                    <Input
                        label="Email"
                        placeholder="you@alex2006hw.com"
                        value={this.state.text}
                        onChangeText={ email => this.setState({ email }) }
                    />
                </CardSection>

                <CardSection>
                    <Input
                        label="Password"
                        placeholder="password"
                        secureTextEntry
                        value={this.state.password}
                        onChangeText={ password => this.setState({ password })}
                    />
                </CardSection>

    <Text style={styles.errorTextStyle}>
                    {this.state.loginError}
                </Text>

                <CardSection>
                    {this.renderButton()}
                </CardSection>
            </Card>
        );
    }
};

const styles = {
    errorTextStyle: {
        fontSize: 20,
        alignSelf: 'center',
        color: 'red'
    }
};

export default LoginForm;