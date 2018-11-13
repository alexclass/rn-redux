import * as T from '../Theme';

export const A = T.A.extend`
  font-size: 14px;
  margin-right: 15px;
  text-decoration: none;
  cursor: pointer;
  text-decoration: ${({ active }) => (active ? 'underline' : 'none')};
`;

export const LogOutButton = T.Button.extend`
  display: inline-block;
  margin-right: 15px;
  cursor: pointer;
  text-decoration: ${({ active }) => (active ? 'underline' : 'none')};
`;
