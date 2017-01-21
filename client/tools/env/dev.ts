import { EnvConfig } from './env-config.interface';

const DevConfig: EnvConfig = {
  ENV: 'DEV',
  WS_SERVER_ADDRESS: 'wss://localhost:1903'
};

export = DevConfig;

