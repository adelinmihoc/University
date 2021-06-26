// @ts-ignore

import { Injectable } from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {Observable} from 'rxjs';
import {User} from './user.model';

@Injectable({
  providedIn: 'root'
})
export class UserService {
  private backendUrl = 'http://localhost/PWLabs/Lab8/backend';
  httpOptions = {
    headers: new HttpHeaders({
      'Content-Type': 'application/json'
    })
  };

  constructor(private httpClient: HttpClient) { }

  getUsers(): Observable<User[]> {
    const url = `${this.backendUrl}/getAllUsers.php`;
    // const url = `http://localhost/PWLabs/Lab8/backend/getAllUsers.php`;
    return this.httpClient.get<Array<User>>(url);
  }

  getUserRoles(): Observable<string[]> {
    const url = `${this.backendUrl}/getUserRoles.php`;
    return this.httpClient.get<Array<string>>(url);
  }

  // tslint:disable-next-line:typedef
  addUser(user: User) {
    const url = `${this.backendUrl}/addUser.php`;
    console.log(user);
    this.httpClient.post(url, user).subscribe(res => {
      console.log('post result %o', res);
    });
  }

  // tslint:disable-next-line:typedef
  deleteUser(userId: number) {
    const url = `${this.backendUrl}/deleteUser.php`;
    const obj = {id: userId};
    const body = JSON.stringify(obj);
    console.log(body);
    return this.httpClient.post(url, body).subscribe(res => {
      console.log('post result %o', res);
    });
  }

  // tslint:disable-next-line:typedef
  updateUser(user: User) {
    const url = `${this.backendUrl}/updateUser.php`;
    console.log(user);
    this.httpClient.post(url, user).subscribe(res => {
      console.log('post result %o', res);
    });
  }

  lookupUsers(name: string): Observable<User[]> {
    const url = `${this.backendUrl}/lookupUser.php`;
    const obj = {name};
    const body = JSON.stringify(obj);
    return this.httpClient.post<Array<User>>(url, body);
  }

  browseUsers(role: string): Observable<User[]> {
    const url = `${this.backendUrl}/browseUsers.php`;
    const obj = {role};
    const body = JSON.stringify(obj);
    return this.httpClient.post<Array<User>>(url, body);

  }
}
