import { Command } from "./command";

export class SetBrightnessCommand extends Command {

    command: 1;
    brightness: number;

    build(): string {
        return `3 ${this.brightness}`
    }

    constructor(...cmd: Partial<SetBrightnessCommand>[]) {
        super({ command: 3 }, ...cmd);
    }
}