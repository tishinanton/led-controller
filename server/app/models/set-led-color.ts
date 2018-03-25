import { Command } from "./command";

export class SetLedColorCommand extends Command {
    
    command: 2;
    red: number;
    green: number;
    blue: number;
    led: number;

    build(): string {
        return `2 ${this.red} ${this.green} ${this.blue} ${this.led}`;
    }

    constructor(...cmd: Partial<SetLedColorCommand>[]) {
        super({ command: 2}, ...cmd);
    }
}