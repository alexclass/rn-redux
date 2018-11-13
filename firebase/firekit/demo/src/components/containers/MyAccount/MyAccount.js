import React, {Component} from 'react';
import { connect } from 'react-redux';
import PropTypes from 'prop-types';
import muiThemeable from 'material-ui/styles/muiThemeable';
import {injectIntl, intlShape} from 'react-intl';
import Paper from 'material-ui/Paper';
import TextField from 'material-ui/TextField';
import RaisedButton from 'material-ui/RaisedButton';
import FontIcon from 'material-ui/FontIcon';
import Avatar from 'material-ui/Avatar';
import * as authActions from '../../store/auth/actions';
import { getValidationErrorMessage, isLinkedWithProvider } from '../../store/auth/selectors';
import { Activity } from '../../containers/Activity';
import { PasswordDialog } from '../../containers/PasswordDialog';
import { ImageCropDialog } from '../../containers/ImageCropDialog';
import { ChangePasswordDialog } from '../../containers/ChangePasswordDialog';
import { DeleteAccountDialog } from '../../containers/DeleteAccountDialog';
import { setDialogIsOpen } from '../../store/dialogs/actions';
import Snackbar from 'material-ui/Snackbar';
import {GoogleIcon, FacebookIcon, GitHubIcon, TwitterIcon} from '../../components/Icons';
import IconButton from 'material-ui/IconButton';
import config from '../../config';
import FlatButton from 'material-ui/FlatButton';

const styles={
  paper:{
    display: 'block',
    minHeight: 300,
    margin:15,
    padding: 15
  },
  header:{
    display:'flex',
    flexDirection: 'column',
    justifyContent: 'center',
    alignItems: 'center',
  },
  container: {
    display: 'flex',
    flexWrap: 'wrap',
    alignItems: 'stretch',
    justifyContent: 'center',
    paddingTop: 80,
  },
  button: {
    marginBottom:10,
    //align: 'left'
  },
  avatar: {
    float: 'right',
    overflow: 'none',
    alignSelf: 'center',
    marginTop:-80,
  },
  exampleImageInput: {
    cursor: 'pointer',
    position: 'absolute',
    top: '0',
    bottom: '0',
    right: '0',
    left: '0',
    width: '100%',
    opacity: '0'
  },
  buttons_container: {
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'space-between',
  },
}

export class MyAccount extends Component {

  constructor(props) {
    super(props);
    this.email = null;
    this.name = null;
    this.password = null;
    this.confirm_password = null;
    this.tempPath = null;
    this.cropper = null;

  }

  handlePhotoUploadSuccess = (snapshot) =>{
    const { setDialogIsOpen, updateUser}=this.props;

    updateUser({photoURL: snapshot.downloadURL});
    setDialogIsOpen('new_user_photo_url', undefined);
  }


  hanleUpdateSubmit = () => {
    const {updateUser} =this.props;

    updateUser({displayName: this.name.getValue()});
  }

  handleKeyDown = (event, onSucces) => {

    if(event.keyCode===13){
      onSucces();
    }
  }


  handlePasswordChange = () => {
    const { auth, reauthenticateUser, setIsEditing} =this.props;

    reauthenticateUser(auth, ()=>{setIsEditing('change_password')});

  }

  handleEmailChangeSubmit = () => {
    const {changeEmail, reauthenticateUser, auth,} =this.props;

    const email=this.email.getValue();
    reauthenticateUser(auth, ()=>{changeEmail(email, this.handlePasswordChangeSuccess)})
  }

  handleDeleteAccount = () => {
    const {setDeleteDialogOpen} =this.props;

    setDeleteDialogOpen(true);
  }

  getProviderIcon = (provider) => {

    const {muiTheme, intl, auth, linkUserWithPopup} =this.props;

    const color=muiTheme.palette.primary2Color;

    switch (provider) {
      case 'google.com':
      return <IconButton
        key={provider}
        disabled={isLinkedWithProvider(auth, provider)}
        onTouchTap={()=>{linkUserWithPopup(provider)}}
        tooltip={intl.formatMessage({id: `link_with_google`})}>
        <GoogleIcon color={color}/>
      </IconButton>
      case 'facebook.com':
      return <IconButton
        key={provider}
        disabled={isLinkedWithProvider(auth, provider)}
        onTouchTap={()=>{linkUserWithPopup(provider)}}
        tooltip={intl.formatMessage({id: `link_with_facebook`})}>
        <FacebookIcon color={color}/>
      </IconButton>
      case 'twitter.com':
      return <IconButton
        key={provider}
        disabled={isLinkedWithProvider(auth, provider)}
        onTouchTap={()=>{linkUserWithPopup(provider)}}
        tooltip={intl.formatMessage({id: `link_with_twitter`})}>
        <TwitterIcon color={color}/>
      </IconButton>
      case 'github.com':
      return <IconButton
        key={provider}
        disabled={isLinkedWithProvider(auth, provider)}
        onTouchTap={()=>{linkUserWithPopup(provider)}}
        tooltip={intl.formatMessage({id: `link_with_github`})}>
        <GitHubIcon color={color}/>
      </IconButton>
      default:
      return undefined;
    }
  }

  render(){
    const {
      intl,
      getValidationErrorMessage,
      auth,
      authError,
      muiTheme,
      sendEmailVerification,
      setIsEditing,
      dialogs,
      setDialogIsOpen
    } =this.props;

    const isSnackbarOpen=auth.error !==undefined
    && auth.error.message
    && auth.error.code!==undefined
    && auth.error.code.indexOf('email')<0
    && auth.error.code.indexOf('password')<0
    && auth.error.code.indexOf('confirm_password')<0;

    return (
      <Activity
        title={intl.formatMessage({id: 'my_account'})}>

        <div style={styles.container}>

          <Paper  zDepth={2} style={styles.paper}>
            <div style={styles.header}>

              <Avatar
                style={styles.avatar}
                size={120}
                src={auth.photoURL}
                icon={<FontIcon className="material-icons" >person</FontIcon>}
              />

              { auth.isEditing &&
                <FlatButton
                  onTouchTap={()=>{
                    setDialogIsOpen('new_user_photo_url', true)
                  }}
                  containerElement='label'
                  primary={true}
                  style={styles.button}
                  icon={
                    <FontIcon
                      className="material-icons">
                      photo_camera
                    </FontIcon>
                  }
                />

              }

              { !auth.isEditing && config.firebase_providers!==null && config.firebase_providers!==undefined &&
                <div style={styles.buttons_container}>
                  {config.firebase_providers.map((p)=>{
                    return this.getProviderIcon(p);
                  })}

                </div>
              }

              { auth.isEditing && <div>
                <TextField
                  id="name"
                  ref={(field) => { this.name = field; }}
                  //underlineShow={false}
                  defaultValue={auth.displayName}
                  onKeyDown={(e)=>{this.handleKeyDown(e, this.hanleUpdateSubmit)}}
                  errorText={getValidationErrorMessage('name')}
                  floatingLabelText={intl.formatMessage({id: 'name'})}
                  type="Text"
                  fullWidth={true}
                /> <br/>
                <TextField
                  id="email"
                  ref={(field) => { this.email = field; }}
                  defaultValue={auth.email}
                  onKeyDown={(e)=>{this.handleKeyDown(e, this.handleEmailChangeSubmit)}}
                  errorText={getValidationErrorMessage('email')}
                  floatingLabelText={intl.formatMessage({id: 'email'})}
                  hintText={intl.formatMessage({id: 'password'})}
                  type="Email"
                  fullWidth={true}
                />
              </div>
            }

            { !auth.isEditing &&  <div>
              <h3>{auth.displayName}</h3>
              <span>
                {auth.email}
                { auth.email &&
                  <IconButton
                    onTouchTap={auth.emailVerified===true?undefined:()=>{sendEmailVerification()}}
                    tooltip={intl.formatMessage({id: auth.emailVerified===true?'email_verified':'email_not_verified'})}>
                    <FontIcon
                      color={auth.emailVerified===true?muiTheme.palette.primary1Color:muiTheme.palette.accent1Color}
                      style={{'paddingLeft': 10}}
                      className="material-icons">
                      {auth.emailVerified===true?'verified_user':'error'}
                    </FontIcon>
                  </IconButton>
                }
              </span>
            </div>
          }


        </div>

        <div style={{marginBottom: 20}}>

        </div>

        <RaisedButton
          label={intl.formatMessage({id: auth.isEditing?'cancel':'edit'})}
          primary={true}
          disabled={auth.isFetching}
          style={styles.button}
          fullWidth={true}
          onTouchTap={()=>{setIsEditing(!auth.isEditing)}}
          icon={
            <FontIcon
              className="material-icons">
              {auth.isEditing?'cancel':'edit'}
            </FontIcon>
          }
        />
        <br/>
        <RaisedButton
          label={intl.formatMessage({id: 'change_password'})}
          disabled={auth.isFetching}
          primary={true}
          fullWidth={true}
          style={styles.button}
          onTouchTap={this.handlePasswordChange}
          icon={
            <FontIcon
              className="material-icons">
              lock
            </FontIcon>
          }
        /> <br/>
        <RaisedButton
          label={intl.formatMessage({id: 'delete_account'})}
          disabled={auth.isFetching}
          secondary={true}
          fullWidth={true}
          onTouchTap={this.handleDeleteAccount}
          icon={
            <FontIcon
              className="material-icons">
              delete
            </FontIcon>
          }
        />

      </Paper>

    </div>

    <PasswordDialog />
    <DeleteAccountDialog />
    <ImageCropDialog
      path={`users/${auth.uid}`}
      fileName={`photoURL`}
      onUploadSuccess={(s)=>{this.handlePhotoUploadSuccess(s) }}
      open={dialogs.new_user_photo_url!==undefined}
      src={dialogs.new_user_photo_url}
      handleClose={()=>{
        setDialogIsOpen('new_user_photo_url', undefined);
      }}
      title={intl.formatMessage({id: 'change_photo'})}
    />

    <ChangePasswordDialog
      open={auth.isEditing==='change_password'}
      title={intl.formatMessage({id: 'change_password'})}
    />

    <Snackbar
      bodyStyle={{height:'100%'}}
      open={isSnackbarOpen}
      message={isSnackbarOpen?auth.error.message:''}
      action="OK"
      autoHideDuration={5000}
      onRequestClose={()=>{authError(undefined)}}
      onActionTouchTap={()=>{authError(undefined)}}
    />

  </Activity>
);

}

}

MyAccount.propTypes = {
  intl: intlShape.isRequired,
  muiTheme: PropTypes.object.isRequired,
  authError: PropTypes.func.isRequired,
  updateUser: PropTypes.func.isRequired,
  changePassword: PropTypes.func.isRequired,
  changeEmail: PropTypes.func.isRequired,
  setNewPhotoURL: PropTypes.func.isRequired,
  updateUserPhoto: PropTypes.func.isRequired,
  linkUserWithPopup: PropTypes.func.isRequired,
  getValidationErrorMessage: PropTypes.func.isRequired,
  setDeleteDialogOpen: PropTypes.func.isRequired,
  reauthenticateUser: PropTypes.func.isRequired,
  sendEmailVerification: PropTypes.func.isRequired,
};


const mapStateToProps = (state) => {
  const { auth, dialogs } = state;
  return {
    auth,
    dialogs,
    getValidationErrorMessage: (fieldID)=>getValidationErrorMessage(auth, fieldID)
  };
};

export const MyAccountTest = injectIntl(muiThemeable()(MyAccount));

export default connect(
  mapStateToProps, {...authActions, setDialogIsOpen  }
)(injectIntl(muiThemeable()(MyAccount)));
