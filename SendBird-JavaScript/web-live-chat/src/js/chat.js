import Sendbird from './sendbird.js';
import Spinner from './elements/spinner.js';
import ChatBoard from './elements/chat-board.js';
import LoginBoard from './elements/login-board.js';
import MessageBoard from './elements/message-board.js';
import { hasClass } from './utils.js';

const ELEMENT_ID = 'sb_chat';
const ERROR_MESSAGE_SDK = 'Please import "SendBird SDK" on first.';
const ERROR_MESSAGE_APP_ID = 'Please pass "APP_ID" when start.';
const ERROR_MESSAGE_CHANNEL_URL = 'Please pass "CHANNEL_URL" when start.';
const ERROR_MESSAGE = 'Please create "sb_chat" element on first.';

const MAX_MESSAGE_COUNT = 100;

window.WebFontConfig = {
  google: { families: ['Lato:400,700'] }
};

let chat;
let sendbird;
let spinner;
let board;
let loginBoard;
let messageBoard;

class LiveChat {
  constructor() {
  }

  start(appId, channelUrl) {
    if (!window.SendBird) {
      console.error(ERROR_MESSAGE_SDK);
      return;
    }
    if (!appId) {
      console.error(ERROR_MESSAGE_APP_ID);
      return;
    }
    if (!channelUrl) {
      console.error(ERROR_MESSAGE_CHANNEL_URL);
      return;
    }
    this._getGoogleFont();

    chat = document.getElementById(ELEMENT_ID);
    if (chat) {
      sendbird = new Sendbird(appId);
      spinner = new Spinner();
      board = new ChatBoard(chat);

      messageBoard = new MessageBoard();
      messageBoard.setScrollEvent(() => {
        sendbird.getMessageList((messageList) => {
          messageBoard.renderMessage(messageList, false, true);
        });
      });
      messageBoard.iconClickEvent(() => {
        let textMessage = messageBoard.getMessage();
        messageBoard.clearInput();
        if (textMessage) {
          sendbird.sendMessage(textMessage, (message) => {
            messageBoard.renderMessage([message], true, false);
            this._removeOverCountMessage();
          });
        }
      });

      loginBoard = new LoginBoard(board.self);
      loginBoard.addLoginBtnClickEvent(() => {
        if (!hasClass(loginBoard.loginBtn, loginBoard.classes.DISABLED)) {
          loginBoard.disableLoginBoard();
          spinner.insert(loginBoard.loginBtn);
          sendbird.connect(loginBoard.userId.value, loginBoard.nickname.value, () => {
            spinner.remove(loginBoard.loginBtn);
            loginBoard.reset();
            spinner.insert(messageBoard.content);
            board.self.replaceChild(messageBoard.self, loginBoard.self);
            this._connectChannel(channelUrl);
          });
        }
      });
    } else {
      console.error(ERROR_MESSAGE);
    }
  }

  _getGoogleFont() {
    var wf = document.createElement('script');
    wf.src = ('https:' == document.location.protocol ? 'https' : 'http') +
      '://ajax.googleapis.com/ajax/libs/webfont/1.5.18/webfont.js';
    wf.type = 'text/javascript';
    wf.async = 'true';
    var s = document.getElementsByTagName('script')[0];
    s.parentNode.insertBefore(wf, s);
  }

  _connectChannel(channelUrl) {
    sendbird.connectChannel(channelUrl, () => {
      sendbird.getMessageList((messageList) => {
        spinner.remove(messageBoard.content);
        messageBoard.renderMessage(messageList, true, false);
        sendbird.createHandler((channel, message) => {
          if (channel.url == channelUrl) {
            let isBottom = messageBoard.isBottom();
            messageBoard.renderMessage([message], isBottom, false);
            if (!isBottom) {
              messageBoard.createBottomBtn();
            } else {
              this._removeOverCountMessage();
            }
          }
        });
      });
    });
  }

  _removeOverCountMessage() {
    let messages = messageBoard.content.children;
    let overCount = messages.length - MAX_MESSAGE_COUNT;
    if (overCount > 0) {
      var i;
      for (i = 0 ; i < overCount ; i++) {
        messageBoard.content.removeChild(messageBoard.content.firstChild);
      }
    }
  }

}

window.liveChat = new LiveChat();
