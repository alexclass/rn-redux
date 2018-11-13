import React, {Component} from 'react';
import _ from 'lodash';
import { connect } from 'react-redux';
import PropTypes from 'prop-types';
import muiThemeable from 'material-ui/styles/muiThemeable';
import {injectIntl, intlShape} from 'react-intl';
import { Activity } from '../../containers/Activity';
import {List, ListItem} from 'material-ui/List';
import Divider from 'material-ui/Divider';
import Avatar from 'material-ui/Avatar';
import FontIcon from 'material-ui/FontIcon';
import {GoogleIcon, FacebookIcon, GitHubIcon, TwitterIcon} from '../../components/Icons';
import IconButton from 'material-ui/IconButton';
import { withFirebase } from '../../src';

class Users extends Component {

  componentDidMount() {
    this.props.watchList('users');
  }

  getProviderIcon = (provider) => {

    const {muiTheme} =this.props;

    const color=muiTheme.palette.primary2Color;

    switch (provider.providerId) {
      case 'google.com':
      return <IconButton key={provider.providerId}>
        <GoogleIcon color={color}/>
      </IconButton>
      case 'facebook.com':
      return <IconButton key={provider.providerId}>
        <FacebookIcon color={color}/>
      </IconButton>
      case 'twitter.com':
      return <IconButton key={provider.providerId}>
        <TwitterIcon color={color}/>
      </IconButton>
      case 'github.com':
      return <IconButton   key={provider.providerId}>
        <GitHubIcon color={color}/>
      </IconButton>
      case 'phone':
      return <IconButton   key={provider.providerId} >
        <FontIcon className="material-icons" color={color} >phone</FontIcon>
      </IconButton>
      case 'password':
      return <IconButton   key={provider.providerId}>
        <FontIcon className="material-icons" color={color} >email</FontIcon>
      </IconButton>
      default:
      return undefined;
    }
  }

  rednerList(users) {
    const {intl, muiTheme} =this.props;


    if(users===undefined){
      return <div></div>
    }

    return _.map(users, (user, key) => {

      return <div key={key}>
        <ListItem
          key={key}
          id={key}
          leftAvatar={<Avatar src={user.photoURL} alt="person" icon={<FontIcon className="material-icons" >person</FontIcon>}/>}
          rightIcon={<FontIcon className="material-icons" color={user.connections?'green':'red'}>offline_pin</FontIcon>}>

          <div style={{display: 'flex'}}>
            <div>
              <div>
                {user.displayName}
              </div>
              <div
                style={{
                  fontSize: 14,
                  lineHeight: '16px',
                  height: 16,
                  margin: 0,
                  marginTop: 4,
                  color: muiTheme.listItem.secondaryTextColor,
                }}>
                <p>
                  {(!user.connections && !user.lastOnline)?intl.formatMessage({id: 'offline'}):intl.formatMessage({id: 'online'})}
                  {' '}
                  {(!user.connections && user.lastOnline)?intl.formatRelative(new Date(user.lastOnline)):undefined}
                </p>
              </div>

            </div>

            <div style={{alignSelf: 'center', flexDirection: 'row', display: 'flex'}}>
              {user.providerData && user.providerData.map(
                (p)=>{
                  return this.getProviderIcon(p);
                })
              }
            </div>
          </div>

        </ListItem>
        <Divider inset={true}/>
      </div>
    });
  }


  render(){
    const {intl, users, muiTheme} =this.props;

    return (
      <Activity
        isLoading={users===undefined}
        title={intl.formatMessage({id: 'users'})}>
        <div >

          <div style={{overflow: 'none', backgroundColor: muiTheme.palette.convasColor}}>
            <List  id='test' style={{height: '100%'}} ref={(field) => { this.list = field; }}>
              {this.rednerList(users)}
            </List>
          </div>

        </div>


      </Activity>
    );

  }

}

Users.propTypes = {
  intl: intlShape.isRequired,
  muiTheme: PropTypes.object.isRequired,
  auth: PropTypes.object.isRequired,
};

const mapStateToProps = (state) => {
  const { lists, auth } = state;
  return {
    users: lists.users,
    auth
  };
};


export default connect(
  mapStateToProps
)(injectIntl(muiThemeable()(withFirebase(Users))));
