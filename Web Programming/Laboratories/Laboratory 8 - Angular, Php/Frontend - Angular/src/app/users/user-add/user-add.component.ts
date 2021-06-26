import { Component, OnInit } from '@angular/core';
import {UserService} from '../shared/user.service';
import {User} from '../shared/user.model';

@Component({
  selector: 'app-user-add',
  templateUrl: './user-add.component.html',
  styleUrls: ['./user-add.component.css']
})
export class UserAddComponent implements OnInit {

  constructor(private userService: UserService) { }

  ngOnInit(): void {
  }

  // tslint:disable-next-line:typedef
  addUser(name: string, username: string, password: string, age: number, role: string,
          profile: string, email: string, webpage: string) {
    const user: User = {name, username, password, age, role, profile, email, webpage} as User;
    console.log(user);
    this.userService.addUser(user);

  }

  Number(value: string): number {
    return Number(value);
  }
}
