import { EnvConfig } from './env-config.interface';

const ProdConfig: EnvConfig = {
  ENV: 'PROD',
  WS_SERVER_ADDRESS: 'wss://127.0.0.1:1903'
};

export = ProdConfig;

